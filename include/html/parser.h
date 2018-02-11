#include <stdio.h>
#include "../../vendor/htmlstreamparser/htmlstreamparser.h"
#include "../../vendor/libyuarel/yuarel.h"
#include "../../include/sql/queries.h"

HTMLSTREAMPARSER* html_init_tag_parser(char *tagName, char *tagAttribute, unsigned int maxTagValueLength);
size_t html_parse_tag_attr(void *buffer, size_t size, size_t nmemb,void *hsp);
