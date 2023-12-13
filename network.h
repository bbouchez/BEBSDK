/*
 *  Network.h
 *  Cross Platform SDK
 *  Low level network access functions
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

#ifndef __NETWORK_H__
#define __NETWORK_H__

#if defined (__TARGET_MAC__)
#include <sys/socket.h>
#include <netinet/in.h>
#define INVALID_SOCKET			-1
#endif

#ifdef __TARGET_LINUX__
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define INVALID_SOCKET          -1
#endif

#if defined (__TARGET_WIN__)
// If winsock.h is used, link with wsock32.lib
// If winsock2.h i used, link with ws2_32.lib
#ifdef __USE_WINSOCK__
#include <winsock.h>
#else
#include <winsock2.h>
#endif
#endif

#if defined (__TARGET_WIN__)
typedef SOCKET TSOCKTYPE;
#endif
#if defined (__TARGET_MAC__)
typedef int TSOCKTYPE;
#endif
#if defined (__TARGET_LINUX__)
typedef int TSOCKTYPE;
#endif

#if defined (__TARGET_WIN__)
bool OpenNetwork (void);
void CloseNetwork (void);
#endif
bool CreateUDPSocket (TSOCKTYPE* sock, unsigned short NumPort, bool shouldReuse);
#if defined (__TARGET_WIN__)
bool ConnectSocket (TSOCKTYPE* sock, unsigned short NumPort, unsigned long IPAddr, HWND hwnd, unsigned int MsgId, unsigned int TempoConnect);
#endif
bool ConnectTCPSocket (TSOCKTYPE* sock, unsigned short NumPort, unsigned long IPAddr, unsigned int TimeOut);
bool DataAvail (TSOCKTYPE sock, unsigned int WaitTimeMS);
void CloseSocket (TSOCKTYPE* sock);

#endif
