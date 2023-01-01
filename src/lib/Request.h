#pragma once
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "str.h"

#define MAX_METHOD_LEN 6
#define MAX_URL_LEN 50


class Request{
    public:
        enum Method{
            GET,
            POST,
            PUT,
            DELETE
        };
    private:
        Method method;
        std::string url;
        bool isBadRequestBool;
    public:
        Request(char* request_str){
            isBadRequestBool = false;
            request_parser(request_str);
        }
    
        void request_parser(char* request_str){
            std::string methodStr;
            int i;
            for(i = 0; i < MAX_METHOD_LEN; i++){
                if(request_str[i] == ' ') break;
                methodStr += toupper(request_str[i]);
            }
            for(int j = 0; j < MAX_URL_LEN; j++){
                i++;
                if(request_str[i] == ' ' || request_str[i] == '?') break;
                url += tolower(request_str[i]);
            }
            if(methodStr == "GET"){
                method = GET;
            }
            else if(methodStr == "POST"){
                method = POST;
            }
            else if(methodStr == "PUT"){
                method = PUT;
            }
            else if(methodStr == "DELETE"){
                method = DELETE;
            }
            else{
                isBadRequestBool = true;
            }
        }

        bool isBadRequest(){
            return isBadRequestBool;
        }

        Method getMethod(){
            return method;
        }

        std::string getMethodString(){
            std::string methodStr;
            switch (method){
                case GET:
                    methodStr = "GET";
                    break;
                case POST:
                    methodStr = "POST";
                    break;
                case PUT:
                    methodStr = "PUT";
                    break;
                case DELETE:
                    methodStr = "DELETE";
                    break;
            }
            return methodStr;
        }

        std::string getUrl(){
            return url;
        }
};

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