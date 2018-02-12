#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../config.h"
#include "../include/db/conn.h"
#include "../include/util/list.h"
#include "../include/util/uri.h"
#include "../include/html/parser.h"

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

	HTMLSTREAMPARSER *hsp;
	hsp = html_init_tag_parser("a", "href", getUriMaxLen());

	ipv4Addr addr;
	initIpv4Addr(&addr);

	if((argc - 1) == 4){
		addr.a = atoi(argv[1]);
		addr.b = atoi(argv[2]);
		addr.c = atoi(argv[3]);
		addr.d = atoi(argv[4]);
	}

	List protocols;

	list_new(&protocols, sizeof(char *), NULL);

	list_append(&protocols, "http");
	//list_append(&protocols, "https");

	//Initialize the random number seed
	srand(mix(clock(), time(NULL), getpid()));

	while(1){
		List uriList;
		list_new(&uriList, sizeof(Uri), NULL);

		generateUriList(
			GENESIS_MAX_IP_GENERATION,
			&protocols,
			&uriList,
			&addr
		);

		printUriList(&uriList);

		httpMulti(
			&uriList, 
			html_parse_tag_attr, 
			hsp, 
			GENESIS_USER_AGENT,
			GENESIS_CONNECT_TIMEOUT, 
			GENESIS_TRANSFER_TIMEOUT_MS
		);

		destroyUriList(&uriList);

		if(GENESIS_SLEEP_BETWEEN_BATCHES > 0){
			sleep(GENESIS_SLEEP_BETWEEN_BATCHES);
		}
	}

	list_destroy(&protocols);

}
