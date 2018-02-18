#ifndef __IF_GENESIS_SQL

/**
 * Nothing too fancy, but it gets the task done
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../vendor/libyuarel/yuarel.h"
#include "../../include/util/string.h"
#include "../../include/util/list.h"
#include "../../include/sql/tables.h"
#include "../../include/db/conn.h"
#include "../../include/util/uri.h"

#define SQL_ADD_CRAWL_HOST "INSERT INTO %s SET `scheme`='%s', `url`='%s', `server`='%s'"
#define SQL_GET_INSPECTED_HOSTS "SELECT %s FROM %s WHERE %s=%d LIMIT %d"
#define SQL_URL_EXISTS "SELECT url FROM crawl_pool WHERE scheme='%s' AND url='%s' LIMIT 1"
#define SQL_MARK_URL_AS_INSPECTED "UPDATE crawl_pool SET inspected=1 WHERE scheme='%s' AND url='%s'"

typedef struct CrawlRecord{
	char *id;
	char *server;
	char *created_at;
	char *inspected;
	char *scheme;
	char *url;
} CrawlRecord;

typedef int handleSQLRecord(MYSQL_ROW row, unsigned int numFields, void *userData);

int sqlSelect(char *sql, handleSQLRecord callback, void *data);
int sqlRecordExists(char *sql);

void addCrawlHost(struct yuarel *url, char *serverName);
unsigned int urlExists(struct yuarel *url);

unsigned int getNonInspectedHosts(handleSQLRecord callback, unsigned int limit, void *data);
int initCrawlRecord(MYSQL_ROW row, CrawlRecord *r);
void destroyCrawlRecord(CrawlRecord *record);

void setUriListAsInspected(List *uriList);
void setUriAsInspected(Uri *uri);

#endif
