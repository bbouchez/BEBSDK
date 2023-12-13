/*
 *  SystemSleep.cpp
 *  Cross Platform SDK
 *  Cross platform functions for system "sleep"
 *
 *  Created by Benoit BOUCHEZ (BEB)
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

#include "SystemSleep.h"

#if defined (__TARGET_WIN__)
#include <windows.h>
#endif

#if defined (__TARGET_MAC__)
#include <unistd.h>
#include <time.h>
#endif

#if defined (__TARGET_LINUX__)
#include <unistd.h>
#include <time.h>
#endif

void SystemSleepMillis(unsigned int MSTime)
{
#if defined (__TARGET_MAC__)
	struct timespec rqtp;
	struct timespec rmtp;

	rqtp.tv_sec = 0;
	rqtp.tv_nsec = MSTime * 1000000;
	nanosleep(&rqtp, &rmtp);
#endif
#if defined (__TARGET_WIN__)
	Sleep(MSTime);
#endif
#if defined (__TARGET_LINUX__)
	usleep(MSTime * 1000);
#endif
}  // SystemSleepMillis
//---------------------------------------------------------------------------