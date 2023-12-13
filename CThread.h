/*
 *  CThread.h
 *  Cross Platform SDK
 *  Thread control class
 *
 * Created by Benoit BOUCHEZ on 14/06/08.
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

30/10/2010:
 - UserData member moved from private to public
*/

#ifndef __CTHREAD_H__
#define __CTHREAD_H__

#include <pthread.h>

typedef void* ThreadFuncType(void*);

class CThread {
private:
  pthread_attr_t ThreadAttributes;
  bool AttributesDone;
  struct sched_param sp;
  pthread_t TheThread;			// OS thread control structure
  
public:
  void* UserData;
  bool ShouldStop;		// Parent application asks for real time thread to stop
  bool IsStopped;			// Signals to parent that thread function is stopped (exited or not started)
  
  CThread (ThreadFuncType *ThreadFunc, const unsigned int Priority, void *Data);
  ~CThread (void);
  
  int StopThread  (const unsigned int MaxStopTimeMs);
};

#endif