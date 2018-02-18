#include "../../include/util/uri.h"

unsigned int initUri(Uri *uri, char *scheme, char *host, unsigned short int port, char *path){
	unsigned int schemeLen = strnlen(scheme, URI_MAX_SCHEME_LENGTH);
	unsigned int hostLen = strnlen(host, URI_MAX_HOST_LENGTH);
	unsigned int pathLen = strnlen(path, URI_MAX_PATH_LENGTH);

	uri->scheme = malloc(schemeLen + 1);
	uri->host = malloc(hostLen + 1);
	uri->port = port > 0 ? port : 0;
	uri->path = malloc(pathLen + 1);

	strncpy(uri->scheme, scheme, schemeLen + 1);
	strncpy(uri->host, host, hostLen + 1);
	strncpy(uri->path, path, pathLen + 1);

	return 0;
}

unsigned int generateUriList(unsigned long int amount, List *protocols, List *uriList, ipv4Addr *addr){
	unsigned long int i=0;

	ipv4Addr ip;
	listNode *proto;
	char *strIp; //You sexy bitch!
	char *defaultPath = "/";

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
			initUri(&u, (char *)proto->data, strIp, 0 , defaultPath);
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
	
	allocLen += strnlen(uri->scheme, URI_MAX_SCHEME_LENGTH) + 1;
	allocLen += strlen(URI_SCHEME_SEPARATOR) + 1;
	allocLen += strnlen(uri->host, URI_MAX_HOST_LENGTH) + 1;
	allocLen += uri->path == NULL ? 0 : strnlen(uri->path, URI_MAX_PATH_LENGTH) + 1;

	str = malloc(allocLen);

	sprintf(str, "%s%s%s%s", uri->scheme, URI_SCHEME_SEPARATOR, uri->host, (uri->path == NULL ? "" : uri->path));

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
	free(uri->scheme);
	free(uri->host);
	free(uri->path);
}

void destroyUriList(List *uriList){
  listNode *node = uriList->head;
  while(node != NULL) {
    destroyUri((Uri*) node->data);
    node = node->next;
  }
}

unsigned int getUriMaxLen(){
	return URI_MAX_SCHEME_LENGTH + strlen(URI_SCHEME_SEPARATOR) + URI_MAX_HOST_LENGTH + URI_MAX_PATH_LENGTH;
}

void dumpUri(Uri *uri){
	printf("\nProto: %s\n", uri->scheme);
	printf("Host : %s\n", uri->host);
	printf("Port : %d\n", uri->port);
	printf("Path : %s\n", uri->path);
}
