#include "../../include/util/string.h"

/**
 * Pass char *dest malloced with 1 byte, the function will redimension the memory size as needed
 */
short int strCat(char *dest, const char *string){
	unsigned long int curLen = strnlen(dest, STRING_MAX_LEN) + 1;

	if(realloc(dest, curLen + strnlen(string, STRING_MAX_LEN) + 1) == NULL){
		return 0;
	}

	strcat(dest, string);
	return 1;
}

unsigned short int intToString(long long int num, char *str){
	unsigned int maxLen = snprintf(NULL, 0, "%lli", LLONG_MAX);

	if(realloc(str, maxLen) == NULL){
		return -1;
	}

	sprintf(str, "%lli", num);
	return 1;
}
