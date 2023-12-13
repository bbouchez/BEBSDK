/*
 *  TargetTypes.h
 *  Cross Platform SDK type definitions
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

/* Versions

28/12/2009:
 - first version

03/01/2010:
 - Windows platform : TPARENTHANDLE changed to HWND / End of line corrected

 27/01/2010:
 - all platforms : THINSTANCE type added

 12/03/2020:
 - added LINUX platform by __TARGET_LINUX__

*/

#if defined (__TARGET_WIN__)
#if defined (__BORLANDC__)
#include <vcl.h>
#else
#include <windows.h>
#endif

typedef HWND TPARENTHANDLE;
typedef HINSTANCE THINSTANCE;

#elif defined (__TARGET_MAC__)
typedef void* TPARENTHANDLE;
typedef void* THINSTANCE;

#elif defined (__TARGET_LINUX__)
typedef void* TPARENTHANDLE;
typedef void* THINSTANCE;
#endif
