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
//! Initialize Winsock and check version. On Windows platform, this function must be called before using any other function in the library
//! \return false if Winsock can not be initialized or if Winsock version is not compatible with functions used in the library
bool OpenNetwork (void);

//! Free all Windows socket ressources allocated to the application
void CloseNetwork (void);
#endif

//! Create a UDP socket. The socket can be used for sending and receiving UDP packets
//! \return true if the socket has been created successfully and can be used.
//! \param NumPort UDP port number for telegram reception (0..65535)
//! \param ShouldReuse if true, ask OS to create a new UDP port even if NumPort is already used in the system
bool CreateUDPSocket (TSOCKTYPE* sock, unsigned short NumPort, bool shouldReuse);

//! Create a TCP socket as a client and tries to connect it to a server in a given amount of time
//! \return true if socket has been created successfully and has connected to the server in the given time
//! \param NumPort : TCP server port to connect to
//! \param IPAddr : IPv4 server address to connect to
//! \param TimeOut : maximum time in milliseconds to connect to the server
bool ConnectTCPSocket (TSOCKTYPE* sock, unsigned short NumPort, unsigned long IPAddr, unsigned int TimeOut);

//! Non blocking function to check if data has been received on the socket and is available for reading
//! \param WaitTimeMS time in milliseconds for the function to wait until data is received. If 0, function returns immediately
//! \return true if at least one packet is ready to be read in the socket
bool DataAvail (TSOCKTYPE sock, unsigned int WaitTimeMS);

//! Close socket (terminates connection if TCP) and marks it as 
void CloseSocket (TSOCKTYPE* sock);

#endif
