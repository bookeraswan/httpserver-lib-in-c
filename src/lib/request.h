#ifndef REQUEST_LIB
#define REQUEST_LIB
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "str.h"

#define MAX_METHOD_LEN 6
#define MAX_URL_LEN 50

typedef struct{
    char  method[MAX_METHOD_LEN];
    char  url[MAX_URL_LEN+1];
}Request;


Request request_parser(char* request_str){
    printf("%s", request_str);
    Request request;
    memset(request.method, 0, MAX_METHOD_LEN);
    memset(request.url, 0, MAX_URL_LEN+1);
    int i;
    for(i = 0; i < MAX_METHOD_LEN; i++){
        if(request_str[i] == ' ') break;
        request.method[i] = request_str[i];
    }
    for(int j = 0; j < MAX_URL_LEN; j++){
        i++;
        if(request_str[i] == ' ' || request_str[i] == '?') break;
        request.url[j] = request_str[i];
    }
    return request;
}

#endif

// /*

// GET / HTTP/1.1
// Host: localhost:2000
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,* /*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1

// */