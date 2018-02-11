#include "../../include/util/uri.h"

void testGenerateUriList(void);

void main(void){

	testGenerateUriList();

}

void testGenerateUriList(void){
	List uriList;
	List protocols;

	list_new(&protocols, sizeof(char *), NULL);

	list_append(&protocols, "http");
	list_append(&protocols, "https");

	list_new(&uriList, sizeof(Uri), NULL);

	generateUriList(2000, &protocols, &uriList);

	printUriList(&uriList);

	destroyUriList(&uriList);
	list_destroy(&protocols);
}
