#include <stdio.h>
#include <stdlib.h>
#include "../../include/db/conn.h"
/**
 * Returns a connection to the database (singleton pattern)
 */
MYSQL* dbConnection(struct DBParams *params){
	static MYSQL* con = NULL;

	if(con != NULL){
		return con;
	}

	con = mysql_init(NULL);
	if( 
		mysql_real_connect(
			con, 
			params->host,
			params->user,
			params->pass,
			params->name, 
			params->port, 
			NULL, 
			CLIENT_MULTI_STATEMENTS
		)
		== 
		NULL
	){
		fprintf(stderr, "Could not connect to database %s", params->name);
		exit(1);
	}

	return con;
}
