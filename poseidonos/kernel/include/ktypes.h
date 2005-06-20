/* PoseidonOS v.1	
	File: ktypes.h
	Date: September 7, 2004*/

#ifndef KTYPES_H
#define KTYPES_H

#define NULL 0

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

typedef enum { false=0,true=1 } bool; /* boolean value */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef int size_t;

#endif
