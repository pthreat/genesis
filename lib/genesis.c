#include "../include/genesis.h"

int handleRecord(MYSQL_ROW row, unsigned int numFields, void *userData){

	CrawlRecord r;
	initCrawlRecord(row, &r);

	Uri u;
	initUri(&u, r.scheme, r.url, 0, "/");
	list_append((List *)userData, &u);

	destroyCrawlRecord(&r);

}

int main(int argc, char *argv[]){

	struct DBParams conParams;

	conParams.host = DB_HOST;
	conParams.user = DB_USER;
	conParams.pass = DB_PASS;
	conParams.name = DB_NAME;
	conParams.port = DB_PORT;

	dbConnection(&conParams);

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

	unsigned int mode;

	while(1){
		List uriList;
		list_new(&uriList, sizeof(Uri), NULL);
		mode = 0;

		getNonInspectedHosts(handleRecord, GENESIS_MAX_IP_GENERATION, &uriList);

		if(uriList.length == 0){
			mode = 1;
			generateUriList(
				GENESIS_MAX_IP_GENERATION,
				&protocols,
				&uriList,
				&addr
			);

		}

		printUriList(&uriList);

		if(mode == 0){
			setUriListAsInspected(&uriList);
		}

		httpMulti(
			&uriList, 
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

const char* getPoolerName(){
	return GENESIS_POOLER_NAME;
}
