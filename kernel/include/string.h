/* File: string.h
   Description: provides basic memory and string operations*/
#include <ktypes.h>

#ifndef STRING_H
#define STRING_H

//copy n bytes from src to dest
void *memcpy(void *dest, const void *src, size_t n);

//copy n bytes from src to dest, guarenteeing correct behavior for overlapping strings
void *memmove(void *dest, const void *src, size_t n);

//copy no more than n bytes of src to dest, stopping when c is found
//return the position in dest one byte past where C was copied,
//or NULL if C was not found in the first N bytes of src.
void *memccpy(void *, void *, int, int);

//set n bytes of s to c
void *memset(void *s, int c, size_t n);

//compare n bytes of s1 and s2
int memcmp(const void *s1, const void *s2, size_t n);

//search n bytes of s for c
void *memchr (const void *s, int c, size_t n);

//copy src to dest
char *strcpy(char *, const char *);

//copy no more than N characters of src to dest
char *strncpy(char *dest, const char *src, size_t n);

//concantinate src onto dest
char *strcat(char *dest, const char *src);

//append no more than n characters from src onto dest
char *strncat(char *dest, const char *src, size_t n);

//compare s1 and s2
int strcmp(const char *s1, const char *s2);

//compare n characters of s1 and s2
int strncmp(const char *s1, const char *s2, size_t n);

///get the length of a string
size_t strlen(const char *);

void str_tolower(char *);

char *strip_whitespace(char *, int);

#endif

