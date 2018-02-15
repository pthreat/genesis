#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "callback.h"
#include "../html/parser.h"
#include "../util/uri.h"
#include "../../config.h"

void httpMulti(List *uriList, char *ua, int connectTimeout, int transferTimeout);
CURL* curlInitHandle(Uri *uri, char *ua, int connectTimeout, int transferTimeout);
