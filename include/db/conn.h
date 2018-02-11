#include <mysql/mysql.h>
#define MYSQL_CONNECT_ERROR 200

struct DBParams {
	char *host;
	char *user;
	char *pass;
	char *name;
	unsigned short port;
};

MYSQL* dbConnection(struct DBParams *params);
