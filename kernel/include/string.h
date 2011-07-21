/* File: string.h
   Description: provides basic memory and string operations*/
#include <ktypes.h>

#ifndef STRING_H
#define STRING_H

//copy n bytes from src to dest
void *memcpy(void *, void *, int);

//copy n bytes from src to dest, guarenteeing correct behavior for overlapping strings
void *memmove(void *, void *, int);

//copy no more than n bytes of src to dest, stopping when c is found
//return the position in dest one byte past where C was copied,
//or NULL if C was not found in the first N bytes of src.
void *memccpy(void *, void *, int, int);

//set n bytes of s to c
void memset(void * s, int n, int c);

//compare n bytes of s1 and s2
int memcmp(void *, void *, int);

//search n bytes of s for c
void *memchr (void *, int, int);

//copy src to dest
char *strcpy(char *, const char *);

//copy no more than N characters of src to dest
char *strncpy (char *, char *, int);

//concantinate src onto dest
char *strcat(char *, char *);

//append no more than n characters from src onto dest
char *strncat(char *, char *, int);

//compare s1 and s2
int strcmp(char *, char *);

//compare n characters of s1 and s2
int strncmp(char *, char *, int);

///get the length of a string
int strlen(const char *);

void tolower(char *);

char *strip_whitespace(char *, int);

#endif

