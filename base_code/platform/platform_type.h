#pragma once
#include <sys/types.h>

// 系统
#ifndef OS_UNIX
#define OS_UNIX
#undef OX_WIN 
#endif


// 变量
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef bool
#define bool unsigned char
#endif

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned short
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

#ifndef uint64
#define uint64 unsigned long long
#endif

#ifndef int8
#define int8 signed char
#endif

#ifndef int16
#define int16 signed short
#endif

#ifndef int32
#define int32 signed int
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#if IS_OS_64
#ifndef size_t
#define size_t unsigned long
#endif
#ifndef ssize_t
#define ssize_t signed long
#endif
#else
#ifndef size_t
#define size_t unsigned int
#endif
#ifndef ssize_t
#define ssize_t signed int
#endif
#endif

// 数值
#define NUM_MAX  0XFFFFFFFF

// 小函数
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MIN(a, b)  ((a) > (b) ? (b) : (a))
