#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../vendor/libyuarel/yuarel.h"
#include "../../include/sql/queries.h"
#include "../../include/util/regex.h"
#include <gumbo.h>

typedef struct MemoryStruct {
	char *memory;
	size_t size;
} MemoryStruct;

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
int parseHrefs(MemoryStruct *memory);
