/* PoseidonOS v.1	
	File: ktypes.h
	Date: September 7, 2004*/

#ifndef KTYPES_H
#define KTYPES_H

#ifndef NULL
//this may be defined already
#define NULL 0
#endif

struct ktime
{
	unsigned short sec:5;
	unsigned short min:6;
	unsigned short hour:5;
};

struct kdate
{
	unsigned short day:5;
	unsigned short month:4;
	unsigned short year:7;
};

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef long unsigned int size_t;

typedef unsigned int bool;

#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

#endif
