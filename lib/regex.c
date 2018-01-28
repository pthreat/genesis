#include "../include/regex.h"

unsigned short int preg_match(char* pattern, char *content){
	regex_t re;

	if(regcomp(&re, pattern, REG_EXTENDED) != 0){
		printf("%s could not compile regex");
	}
	
	return regexec(&re, content, 0, NULL, 0) == 0 ? 1 : 0;
}
