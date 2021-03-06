#ifndef __GENESIS_URI
#define __GENESIS_URI

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "net/ipgen.h"
#include "list.h"

#define URI_MAX_SCHEME_LENGTH  10
#define URI_MAX_HOST_LENGTH 255
#define URI_MAX_PATH_LENGTH 3000
#define URI_SCHEME_SEPARATOR "://"

typedef struct Uri{
	char *scheme;
	char *host;
	unsigned short int port;
	char *path;
} Uri;

unsigned int initUri(Uri *uri, char *scheme, char *host, unsigned short int port, char *path);
unsigned int generateUriList(unsigned long int amount, List *protocols, List *uriList, ipv4Addr *addr);
char *uriToString(Uri *uri);
unsigned int getUriMaxLen();

void dumpUri(Uri *uri);
void printUri(Uri *uri);
void printUriList(List *uriList);
void destroyUriList(List *uriList);
void destroyUri(Uri *uri);

#endif
