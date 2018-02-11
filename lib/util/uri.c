#include "../../include/util/uri.h"

unsigned int initUri(Uri *uri, char *proto, char *host, unsigned short int port, char *path){
	unsigned int protoLen = strnlen(proto, URI_MAX_PROTO_LENGTH) + 1;
	unsigned int hostLen = strnlen(host, URI_MAX_HOST_LENGTH) + 1;
	unsigned int pathLen = 0;

	uri->proto = NULL;
	uri->host = NULL;
	uri->port = port > 0 ? port : 0;
	uri->path = NULL;

	uri->proto = malloc(protoLen);
	strncpy(uri->proto, proto, protoLen);
	uri->host = malloc(strnlen(host, hostLen));
	strncpy(uri->host, host, hostLen);

	if(path != NULL){
		pathLen = strnlen(path, URI_MAX_PATH_LENGTH);
		uri->path = malloc(URI_MAX_PATH_LENGTH);
		strncpy(uri->path, path, pathLen);
	}

	if(port > 0){
		uri->port = port;
	}

	return 0;
}

unsigned int generateUriList(unsigned long int amount, List *protocols, List *uriList, ipv4Addr *addr){
	unsigned long int i=0;

	ipv4Addr ip;
	listNode *proto;
	char *strIp; //You sexy bitch!

	for(i=0; i < amount; i++){

		ip.a = addr->a;
		ip.b = addr->b;
		ip.c = addr->c;
		ip.d = addr->d;

		strIp = malloc(16);

		proto = protocols->head;

		generateRandomIp(&ip);

		sprintf(strIp, "%s", ipv4AddrToString(&ip));

		while(proto != NULL){
			Uri u;
			initUri(&u, (char *)proto->data, strIp, 0 , NULL);
			list_append(uriList, &u);
			proto = proto->next;
		}

		free(strIp);
	}

	return 0;
}

char *uriToString(Uri *uri){
	char *str;
	unsigned int allocLen = 0;
	
	allocLen += strnlen(uri->proto, URI_MAX_PROTO_LENGTH) + 1;
	allocLen += strlen(URI_PROTO_SEPARATOR) + 1;
	allocLen += strnlen(uri->host, URI_MAX_HOST_LENGTH) + 1;
	allocLen += uri->path == NULL ? 0 : strnlen(uri->path, URI_MAX_PATH_LENGTH) + 1;

	str = malloc(allocLen);

	sprintf(str, "%s%s%s%s", uri->proto, URI_PROTO_SEPARATOR, uri->host, (uri->path == NULL ? "" : uri->path));

	return str;
}

void printUri(Uri *uri){
   char *str = uriToString(uri);
	printf("%s\n", str);
	free(str);
}

void printUriList(List *uriList){
  listNode *node = uriList->head;
  while(node != NULL) {
    printUri((Uri*) node->data);
    node = node->next;
  }
}

void destroyUri(Uri *uri){
	free(uri->proto);
	free(uri->host);
	if(uri->path != NULL){
		free(uri->path);
	}
}

void destroyUriList(List *uriList){
  listNode *node = uriList->head;
  while(node != NULL) {
    destroyUri((Uri*) node->data);
    node = node->next;
  }
}

unsigned int getUriMaxLen(){
	return URI_MAX_PROTO_LENGTH + strlen(URI_PROTO_SEPARATOR) + URI_MAX_HOST_LENGTH + URI_MAX_PATH_LENGTH;
}

void dumpUri(Uri *uri){
	printf("\nProto: %s\n", uri->proto);
	printf("Host : %s\n", uri->host);
	printf("Port : %d\n", uri->port);
	printf("Path : %s\n", uri->path);
}
