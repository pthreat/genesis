#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../../include/constants.h"
#include "../../include/html/parser.h"
#include "../../config.h"

unsigned short int httpSingle(char *urlOrIp, char *tagName, char *tagAttribute, unsigned long int tagValueLength);
