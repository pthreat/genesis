#include "include/rslvr.h"


int rslvHostname(char *host, List *ipList){

	struct addrinfo hints, *res;
	int errcode;
	char addrstr[100];
	void *ptr;

	memset (&hints, 0, sizeof (hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;

	errcode = getaddrinfo (host, NULL, &hints, &res);

	if (errcode != 0){
		perror ("getaddrinfo");
		return -1;
	}

	while (res){
		inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100);

		switch (res->ai_family){
			case AF_INET:
				ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
				break;
			case AF_INET6:
				ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
				break;
		}

		inet_ntop (res->ai_family, ptr, addrstr, 100);

		list_append(ipList, addrstr);
				
		res = res->ai_next;
	}

	return 0;
}

void rslvHostList(List *hostList){
	listNode *host = hostList->head;

	while(host != NULL){
		List ipList;
		list_new(&ipList, 49, NULL);

		CrawlRecord *record = (CrawlRecord *)host->data;

		rslvHostname(record->url, &ipList);
		listNode *node = ipList.head;	

		while(node != NULL){
			addRslvrRecord(record->id, (char *)node->data);
			node = node->next;
		}
		
		list_destroy(&ipList);
		host = host->next;
	}

}

int main() {

	struct DBParams conParams;

	conParams.host = DB_HOST;
	conParams.user = DB_USER;
	conParams.pass = DB_PASS;
	conParams.name = DB_NAME;
	conParams.port = DB_PORT;

	dbConnection(&conParams);

	while(1){
		List recordList;
		list_new(&recordList, sizeof(CrawlRecord), NULL);

		getHostsThatNeedAddressResolution(handleCrawlRecord, GENESIS_MAX_IP_GENERATION, &recordList);

		if(recordList.length > 0){
			rslvHostList(&recordList);
		}

	}

	return 0;
}
