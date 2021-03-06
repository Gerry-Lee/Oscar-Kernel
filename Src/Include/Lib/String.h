#ifndef _STRING_H
#define _STRING_H

#include "Type.h"
#include "Memory.h"

unsigned long strlen(const char * str);
char *strcpy(char *dest, const char *src);
int strncasecmp(const char *s1, const char *s2, unsigned long len);
int strcasecmp(const char *s1, const char *s2);
char *strncpy(char *dest, const char *src, unsigned int count);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, unsigned long count);
int strcmp(const char *cs, const char *ct);
int strncmp(const char *cs, const char *ct, unsigned long count);
char *skip_spaces(const char *str);
unsigned long strnlen(const char *s, unsigned long count);
char *strstr(const char *s1, const char *s2);
int findstr(unsigned char *data, int size, const char *str, int len);
static inline char tolower(char c);
static inline char toupper(char c);
static inline char isspace(char c);

static inline char isspace(char c)
{
	if (c == ' ')
		return 1;
	return 0;
}

static inline char tolower(char c)
{
	return c - 0x20;
}

static inline char toupper(char c)
{
	return c + 0x20;
}


#endif