#include "../../include/sql/queries.h"

/**
 * Adds a host to the crawling table
 */
void addCrawlHost(struct yuarel *url, char *serverName){
	char *sql = malloc(2048); 
	sprintf(
		sql,
		SQL_ADD_CRAWL_HOST,
		TBL_CRAWL_HOSTS,
		url->scheme,
		url->host,
		serverName
	);

	printf("%s\n",sql);
	mysql_query(dbConnection(NULL), sql);
	free(sql);
}

void setUriAsInspected(Uri *url){
	char *sql = malloc(2048);
	sprintf(
		sql,
		SQL_MARK_URL_AS_INSPECTED,
		url->scheme,
		url->host
	);

	printf("%s\n",sql);

	mysql_query(dbConnection(NULL), sql);

	free(sql);
}

void setUriListAsInspected(List *uriList){
	listNode *node = uriList->head;
	while(node != NULL) {
		setUriAsInspected((Uri*)node->data);
		node = node->next;
	}
}

unsigned int urlExists(struct yuarel *url){

	char *sql = malloc(2048); 

	sprintf(
		sql,
		SQL_URL_EXISTS,
		url->scheme == NULL ? "http" : url->scheme,
		url->host
	);

	unsigned int res = sqlRecordExists(sql);

	free(sql);

	return res;
}

unsigned int getNonInspectedHosts(handleSQLRecord callback, unsigned int limit, void *data){
	char *sql = malloc(2048);

	sprintf(
		sql, 
		SQL_GET_INSPECTED_HOSTS,
		TBL_CRAWL_HOSTS_FIELDS,
		TBL_CRAWL_HOSTS,
		TBL_CRAWL_HOSTS_INSPECTED_FIELD,
		0,
		limit
	);

	sqlSelect(sql, callback, data);

	free(sql);

	return 0;
}

int initCrawlRecord(MYSQL_ROW row, CrawlRecord *record){
	unsigned int idLen = strnlen((char *)row[0], 30);
	unsigned int serverLen = strnlen((char *)row[1], 30);
	unsigned int createdAtLen = strnlen((char *)row[2], 20);
	unsigned int inspectedLen = strnlen((char *)row[3],2);
	unsigned int schemeLen = strnlen((char *)row[4], 8);
	unsigned int urlLen = strnlen((char *)row[5],300);

	record->id = malloc(idLen+1);
	sprintf(record->id, "%s", row[0]);

	record->server = malloc(serverLen+1);
	sprintf(record->server, "%s", row[1]);

	record->created_at = malloc(createdAtLen + 1);
	sprintf(record->created_at, "%s", row[2]);

	record->inspected = malloc(inspectedLen + 1);
	sprintf(record->inspected, "%s", row[3]);

	record->scheme = malloc(schemeLen + 1);
	sprintf(record->scheme, "%s", row[4]);

	record->url = malloc(urlLen + 1);
	sprintf(record->url, "%s", row[5]);
}

void destroyCrawlRecord(CrawlRecord *record){
	free(record->id);
	free(record->server);
	free(record->created_at);
	free(record->inspected);
	free(record->scheme);
	free(record->url);
}

int sqlSelect(char *sql, handleSQLRecord callback, void *data){

	if(mysql_query(dbConnection(NULL), sql)){
		return -1;
	}

	MYSQL_RES *res = mysql_store_result(dbConnection(NULL));

	if(res == NULL){
		return -2;
	}

	unsigned int numFields = mysql_num_fields(res);

	MYSQL_ROW row;

	while( (row = mysql_fetch_row(res)) ){
		handleRecord(row, numFields, data);
	}

	mysql_free_result(res);

	return 0;
}

int sqlRecordExists(char *sql){

	if(mysql_query(dbConnection(NULL), sql)){
		return -1;
	}

	MYSQL_RES *res = mysql_store_result(dbConnection(NULL));

	if(res == NULL){
		return -2;
	}

	unsigned int numFields = mysql_num_fields(res);
	unsigned int ret = mysql_fetch_row(res) == NULL ? 0 : 1;

	mysql_free_result(res);

	return ret;
}
