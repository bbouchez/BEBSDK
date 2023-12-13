/*
 *  CThread.cpp
 *  Cross Platform SDK
 *  Thread control class
 *
 *  Created by Benoit BOUCHEZ on 14/06/08.
 *
 * Copyright (c) 2023 Benoit BOUCHEZ
 * License : MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/* Release notes
 31/12/2009:
 - inclusion of release notes
 - ThreadWait function renamed and moved to XPlatformUtils (function not related specifically to threads)
 - StopThread method uses SystemWaitMS function

 30/10/2010:
 - UserData member moved from private to public

 04/07/2011
 - deleted wait after thread stop in StopThread method. When the isStopped flag is high, it means that pthread_exit() will be reached.
   There is no risk since the thread function is static.

 25/05/2020
 - added support for Linux targets (use __TARGET_LINUX__ define)

 20/07/2021
 - bug corrected in StopThread : time was in 10 ms step, not 1 ms

 19/11/2023
 - code updated to use SystemSleep SDK module
 */

#ifdef __TARGET_WIN__
#if defined __BORLANDC__
#include <vcl.h>
#else
#include <windows.h>
#endif
#endif
#ifdef __TARGET_MAC__
#include "string.h"
#include <unistd.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach/thread_policy.h>
#endif
#include "CThread.h"
#include "SystemSleep.h"
#include <stdio.h>
#include <string.h>

CThread::CThread (ThreadFuncType *ThreadFunc, const unsigned int Priority, void *Data)
{
  int thread_result;
#ifdef __TARGET_MAC__
    mach_timebase_info_data_t   tbinfo;
    double clock2abs;
    //thread_time_constraint_policy_data_t    policy;
    thread_extended_policy_data_t extendedPolicy;
    thread_precedence_policy_data_t precedencePolicy;
    kern_return_t   kr;
#endif
#ifdef __TARGET_LINUX__
    int policy;
#endif

  // Initialize members
  ShouldStop=true;
  IsStopped=true;
  AttributesDone=false;
  UserData=Data;

  // Initialize thread attributes with default values
  thread_result=pthread_attr_init(&ThreadAttributes);
  if (thread_result!=0)
    return;
  else AttributesDone=true;

#ifdef __TARGET_LINUX__
    // Linux threads are created with SCHED_OTHER policy by default
    // This policy does not accept high priority, so we switch first the thread to SCHED_FIFO
    policy = SCHED_FIFO;
    pthread_attr_setschedpolicy(&ThreadAttributes, policy);
#endif

    // Set thread priority
    memset(&sp, 0, sizeof(struct sched_param));
    sp.sched_priority=Priority;
    thread_result=pthread_attr_setschedparam(&ThreadAttributes, &sp);
    if (thread_result!=0)
    {
        // TODO : maybe report a warning but start anyway ?
        printf ("CThread : pthread_attr_setschedparam failed (%d)\n", thread_result);
        return;
    }

#ifdef __TARGET_MAC__
    mach_timebase_info(&tbinfo);
    clock2abs=((double)tbinfo.denom/(double)tbinfo.numer)*1000000;

    /*
    extendedpolicy.period=1;        // 1ms
    extendedpolicy.computation=1;   // 1ms of work
    extendedpolicy.constraint=2;
    extendedpolicy.preemptible=FALSE;
    */
    extendedPolicy.timeshare=0;
#endif


  // Start the thread
  ShouldStop=false;
  thread_result=pthread_create (&TheThread, &ThreadAttributes, ThreadFunc, (void*)this);

#ifdef __TARGET_MAC__
    if (thread_result!=0)
    {
        kr=thread_policy_set(pthread_mach_thread_np(TheThread), THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t)&extendedPolicy, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
        if (kr!=KERN_SUCCESS)
        {
            printf ("Can't set thread policy\n");
        }

        //precedencePolicy.importance = THREAD_IMPORTANCE;
        precedencePolicy.importance = 30;
        kr = thread_policy_set(pthread_mach_thread_np(TheThread), THREAD_PRECEDENCE_POLICY,(thread_policy_t)&precedencePolicy,THREAD_PRECEDENCE_POLICY_COUNT);
        if (kr != KERN_SUCCESS)
        {
            printf("Couldn't set thread precedence policy\n");
        }
    }
#endif

    if (thread_result!=0)
        return;
    else IsStopped=false;  // Signals that thread has started
}  // CThread::CThread
//---------------------------------------------------------------------------

int CThread::StopThread  (const unsigned int MaxStopTimeMs)
{
  unsigned int TryCounter=0;

  // Wait for the thread to stop
  ShouldStop=true;
  while ((TryCounter<MaxStopTimeMs)&&(IsStopped==false))
  {
    TryCounter+=1;
    SystemSleepMillis(1);
  }

  if (IsStopped==false) return -1;		// Thread can not be stopped
  return 0;
}  // CThread::StopThread
//---------------------------------------------------------------------------

CThread::~CThread (void)
{
  // Check that thread is stopped before destroying it
  if (IsStopped==false)
    StopThread (2000);

  pthread_attr_destroy(&ThreadAttributes);
}  // CThread::~CThread
//---------------------------------------------------------------------------
