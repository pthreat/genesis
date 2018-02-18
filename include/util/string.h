#ifndef __IF_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define STRING_MAX_LEN 1024
short int strCat(char *dest, const char *string);
unsigned short int intToString(long long int num, char *buf);

#endif
