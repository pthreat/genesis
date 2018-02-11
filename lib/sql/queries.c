#include <stdio.h>
#include <stdlib.h>
#include "../../include/sql/tables.h"
#include "../../include/sql/queries.h"
#include "../../include/db/conn.h"

/**
 * Adds a host to the crawling table
 */
void addCrawlHost(char *host){
	char *sql = malloc(1024); 
	sprintf(sql, SQL_ADD_CRAWL_HOST, TBL_CRAWL_HOSTS, host);
	printf("%s\n",sql);
	mysql_query(dbConnection(NULL), sql);
	free(sql);
}

