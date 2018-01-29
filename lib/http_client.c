#include <stdio.h>
#include <curl/curl.h>
#include <mysql/mysql.h>

#include "../include/db.h"
#include "../include/http_client.h"
#include "../vendor/htmlstreamparser/htmlstreamparser.h"
#include "../vendor/libyuarel/yuarel.h"
#include "../include/constants.h"
#include "../include/tableNames.h"
#include "../include/sqlQueries.h"
#include "../config.h"

void addCrawlHost(char *host){
	char *sql = malloc(1024); 
	sprintf(sql, SQL_ADD_CRAWL_HOST, TBL_CRAWL_HOSTS, host);
	printf("%s\n",sql);
	mysql_query(dbConnection(NULL), sql);
}

static size_t attr_callback(void *buffer, size_t size, size_t nmemb,void *hsp){

	size_t realsize = size * nmemb, p;

	for(p = 0; p < realsize; p++) {
		struct yuarel url;
		html_parser_char_parse(hsp, ((char *)buffer)[p]);

		if(
				html_parser_cmp_tag(hsp, "a", 1)     && 
				html_parser_cmp_attr(hsp, "href", 4) &&
				html_parser_is_in(hsp, HTML_VALUE_ENDED)
		  )
		{
			char* parsed = malloc(2048);
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

unsigned short int httpGet(char *urlOrIp, char *tagName, char *tagAttribute, unsigned long int maxTagValueLength){

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
	curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, GENESIS_CONNECT_TIMEOUT_MS);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, GENESIS_USER_AGENT);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, attr_callback);
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
