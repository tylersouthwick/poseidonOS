/* File: string.h
   Description: provides basic memory and string operations*/
#include <ktypes.h>

#define size_t int
//copy n bytes from src to dest
void *memcpy(void *dest, void *src, size_t n);

//copy n bytes from src to dest, guarenteeing correct behavior for overlapping strings
void *memmove(void *dest, void *src, size_t n);

//copy no more than n bytes of src to dest, stopping when c is found
//return the position in dest one byte past where C was copied,
//or NULL if C was not found in the first N bytes of src.
void *memccpy(void *dest, void *src, int c, size_t n);

//set n bytes of s to c
void memset(void *s, int c, size_t n);

//compare n bytes of s1 and s2
int memcmp(void *s1, void *s2, size_t n);

//search n bytes of s for c
void *memchr (void *s, int c, size_t n);

//sopy src to dest
char *strcpy(char *dest, char *src);

//copy no more than N characters of src to dest
char *strncpy (char *dest, char *src, size_t n);

//concantinate src onto dest
char *strcat(char *dest, char *src);

//append no more than n characters from src onto dest
char *strncat(char *dest, char *src, size_t n);

//compare s1 and s2
bool strcmp(char *s1, char *s2);

//compare n characters of s1 and s2
int strncmp(char *s1, char *s2, size_t n);

///get the length of a string
int strlen(char *str);

void tolower(char *str);

char *strip_whitespace(char *name, int len);
