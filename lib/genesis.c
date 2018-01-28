#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#include "../config.h"

#include "../include/db.h"
#include "../include/constants.h"
#include "../include/http_client.h"
#include "../include/ipgen.h"
#include "../include/regex.h"

int main(int argc, char *argv[]){

	struct DBParams conParams;

	conParams.host = DB_HOST;
	conParams.user = DB_USER;
	conParams.pass = DB_PASS;
	conParams.name = DB_NAME;
	conParams.port = DB_PORT;

	if(dbConnection(&conParams) == NULL){
		fprintf(stderr, "Could not connect to database %s", conParams.name);
		exit(MYSQL_CONNECT_ERROR);
	}

	char *ip = NULL;
	int a=-1,b=-1,c=-1,d=-1;

	//Initialize the random number seed
	srand(mix(clock(), time(NULL), getpid()));

	a = atoi(argv[1]) > -1 ? atoi(argv[1]) : a;
	b = atoi(argv[2]) > -1 ? atoi(argv[2]) : b;
	c = atoi(argv[3]) > -1 ? atoi(argv[3]) : c;
	d = atoi(argv[4]) > -1 ? atoi(argv[4]) : d;

	while(TRUE){
		ip = generateRandomIp(a,b,c,d);
		char *http = malloc(30);
		char *https = malloc(30);

		sprintf(http, "http://%s",ip);
		sprintf(https, "https://%s",ip);

		printf("Trying %s ...\n", http);
		httpGet(http, "a", "href", HOST_NAME_MAX * 2);
		printf("Trying %s ...\n", https);
		httpGet(https, "a", "href", HOST_NAME_MAX * 2);
		free(ip);
		free(http);
		free(https);
	}

}
