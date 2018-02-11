#include <stdio.h>
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
	mysql_real_connect(
		con, 
		params->host,
		params->user,
		params->pass,
		params->name, 
		0, 
		NULL, 
		CLIENT_MULTI_STATEMENTS
	);

	return con;
}
