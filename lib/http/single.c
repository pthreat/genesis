#include "../../include/http/single.h"

unsigned short int httpSingle(char *urlOrIp, char *tagName, char *tagAttribute, unsigned long int maxTagValueLength){

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

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

	curl_easy_setopt(curl, CURLOPT_URL, urlOrIp);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, GENESIS_CONNECT_TIMEOUT_MS);
	//curl_easy_setopt(curl, CURLOPT_USERAGENT, GENESIS_USER_AGENT);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, html_parse_tag_attr);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, hsp);

	res = curl_easy_perform(curl);

	if(res == CURLE_OK){
		char *url = NULL;
		curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, url);
		if(url){
			printf("Redirect to: %s\n",url);
		}
	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();
	html_parser_cleanup(hsp);
	return EXIT_SUCCESS;
}
