#include "../../include/html/parser.h"

#define PARSER_HREF_REGEX "href=[\"\']?([^\"\'>]+)[\"\']?"

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	strncpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = '\0';

	return realsize;
}

void searchLinks(GumboNode *node){

	if (node->type != GUMBO_NODE_ELEMENT) {
		return;
	}

	unsigned int i = 0;
	GumboAttribute* href;
	struct yuarel url;
	char *parsed = malloc(2048);

	if (node->v.element.tag == GUMBO_TAG_A &&
		(href = gumbo_get_attribute(&node->v.element.attributes, "href"))
	) {

		sprintf(parsed, "%s", href->value);

		if(-1 == yuarel_parse(&url, parsed)){
			puts("Could not parse href");
		}

		if(url.host!= NULL){
			addCrawlHost(url.host);
		}
	}

	free(parsed);

	GumboVector* children = &node->v.element.children;
	
	for (i = 0; i < children->length; ++i) {
		searchLinks((GumboNode*)children->data[i]);
	}

}

int parseHrefs(MemoryStruct *mem){

	printf("%s",mem->memory);
	GumboOutput *out = gumbo_parse(mem->memory);
	searchLinks(out->root);
	gumbo_destroy_output(&kGumboDefaultOptions, out);
}
