#include "../../include/html/parser.h"

/**
 * Returns a properly initialized HTMLSTREAMPARSER pointer
 */
HTMLSTREAMPARSER* html_init_tag_parser(char *tagName, char *tagAttribute, unsigned int maxTagValueLength){
	HTMLSTREAMPARSER *hsp;

	char val[maxTagValueLength];
	char tag[strlen(tagName)];
	char attr[strlen(tagAttribute)];

	hsp = html_parser_init();

	html_parser_set_tag_to_lower(hsp, 1);
	html_parser_set_attr_to_lower(hsp, 1);
	html_parser_set_tag_buffer(hsp, tag, sizeof(tag));
	html_parser_set_attr_buffer(hsp, attr, sizeof(attr));
	html_parser_set_val_buffer(hsp, val, maxTagValueLength);

	return hsp;
}

/**
 * Parses an attribute from an HTML tag
 */
size_t html_parse_tag_attr(void *buffer, size_t size, size_t nmemb, void *hsp){
	size_t realsize = size * nmemb, p;
	char *parsed;
	struct yuarel url;
	char c;

	for(p = 0; p < realsize; p++) {
		c = ((char *)buffer)[p];
		html_parser_char_parse(hsp, c);

		if(
				html_parser_cmp_tag(hsp, "a", 1)     && 
				html_parser_cmp_attr(hsp, "href", 4) &&
				html_parser_is_in(hsp, HTML_VALUE_ENDED)
		  )
		{
			parsed = malloc(2048);
			html_parser_val(hsp)[html_parser_val_length(hsp)] = '\0';

			sprintf(parsed,"%s",html_parser_val(hsp));

			if(-1 == yuarel_parse(&url, parsed)){
				puts("Could not parse URL");
				continue;
			}

			if(url.host != NULL){
				addCrawlHost(url.host);
			}

			free(parsed);
		}
	}

	return realsize;

}
