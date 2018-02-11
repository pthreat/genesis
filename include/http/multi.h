#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "callback.h"
#include "../html/parser.h"
#include "../util/uri.h"
#include "../../config.h"

void httpMulti(List *uriList, curl_callback callback, void *write_buffer , char *ua, int connectTimeout, int transferTimeout);
CURL* curlInitHandle(Uri *uri, curl_callback callback, void *writeBuffer, char *ua, int connectTimeout, int transferTimeout);
