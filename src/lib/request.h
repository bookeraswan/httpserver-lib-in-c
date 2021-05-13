#ifndef REQUEST_LIB
#define REQUEST_LIB
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "str.h"

#define MAX_METHOD_LEN 6
#define MAX_URL_LEN 20

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


// long simplehash(char* word){
//     int word_length = strlen(word);
//     unsigned long hash = 0;
//     for(int i = 1; i <= word_length; i++){
//         hash += floor(pow((double)word[i] + (double)i, (double)i));
//     }
//     return hash;
// }

// struct token{
//     char text[100];
// };


// void list(char* request_str, struct token* request_parts[]){
//     int request_str_len = strlen(request_str);
//     for(int i = 0; i < 50; i++){
//         struct token* newToken = (struct token*)malloc(sizeof(struct token));
//         request_parts[i] = newToken;
//     }
//     int token_idx = 0;
//     for(int i = 0; i < request_str_len; i++){
//         if(request_str[i] == ' ' || request_str[i] == '\n'){
//             token_idx++;
//         }
//         else{
//             char temp[1];
//             temp[0] = request_str[i];
//             strcat(request_parts[token_idx]->text, temp);
//         }
//     }
    
//     for(int i = 0; i < 50; i++){
//         if(request_parts[i]->text[0] == '\0') break;
//         printf("Token:\t");
//         printf("%s\n", request_parts[i]->text);
//     }
// }



// Request request_parser(char* request_str){
//     Request request;
//     struct token* request_parts[50];
//     printf("%s = %ld", "Host", simplehash("Host"));
//     list(request_str, request_parts);
//     for(int i = 0; i < 50; i++){
//         if(request_parts[i]->text[0] == '\0') break;
//         request_parts[i]->text;
//         // switch (expression)
//         // {
//         // case /* constant-expression */:
//         //     /* code */
//         //     break;
        
//         // default:
//         //     break;
//         // }
//     }

//     return request;
// }

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