// Copyright Siemens Corporate Research Inc. 2007
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _INVENTOR_WINDOWS_STANDARD_H_
#define _INVENTOR_WINDOWS_STANDARD_H_

//#define NOMINMAX
#include <windows.h>

#ifdef __cplusplus
#include <algorithm>
#endif // __cplusplus

typedef __int64 int64_t;

//typedef uint64_t __uint64;
typedef unsigned __int64 __uint64;

#define snprintf _snprintf
//#define glGetProcAddress wglGetProcAddress

#endif // _INVENTOR_WINDOWS_STANDARD_H_

