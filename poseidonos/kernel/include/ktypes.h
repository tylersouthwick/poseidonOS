/* PoseidonOS v.1	
	File: ktypes.h
	Date: September 7, 2004*/

#ifndef KTYPES_H
#define KTYPES_H

#define uchar_t unsigned char
#define ushort_t unsigned short
#define uint_t unsigned int;
#define ulong_t unsigned long;

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

#endif
