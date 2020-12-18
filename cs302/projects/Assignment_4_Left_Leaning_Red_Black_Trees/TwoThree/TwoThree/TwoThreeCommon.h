#pragma once

#include <stdint.h>
#include <stdio.h>
#include <cassert>
#include <cstdlib>
#include <cstring>

typedef unsigned char      U08;
typedef signed char        S08;
typedef unsigned short     U16;
typedef signed short       S16;
typedef unsigned long      U32;
typedef signed long        S32;
typedef uint64_t  U64;
typedef int64_t     S64;
typedef unsigned char      Utf08_t;
typedef unsigned short     Utf16_t;
typedef unsigned long      Utf32_t;
typedef void*              Handle_t;

#define Min(x,y)			(((x) < (y)) ? (x) : (y))
#define Max(x,y)			(((x) > (y)) ? (x) : (y))
#define ArraySize(x)		(sizeof(x) / (sizeof((x)[0])))
#define SafeDelete(x)		{ if (NULL != (x)) { delete (x);     (x) = NULL; } }
#define SafeDeleteArray(x)	{ if (NULL != (x)) { delete [] (x);  (x) = NULL; } }