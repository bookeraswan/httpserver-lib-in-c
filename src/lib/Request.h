#pragma once
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <unordered_map>
#include "str.h"
#include "LogColors.h"

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
        class Query{
            private:
                std::unordered_map<std::string, std::string> query;
                std::string queryString;
                void add(std::string key, std::string value){
                    query[stringReplaceAll(key, "%20", " ")] = stringReplaceAll(value, "%20", " ");
                    // query[key] = value;
                }
            public:
            Query(std::string queryString){
                this->queryString = queryString;
            }
            void parse(){
                std::string keyAcc;
                std::string valueAcc;
                bool isKey = true;
                for(int i = 0; i < queryString.size(); i++){
                    if(queryString[i] == '&'){
                        add(keyAcc, valueAcc);
                        keyAcc = "";
                        valueAcc = "";
                        isKey = true;
                    }
                    else if(queryString[i] == '='){
                        isKey = false;
                    }
                    else if(isKey){
                        keyAcc += queryString[i];
                    }
                    else{
                        valueAcc += queryString[i];
                    }

                    if(i == queryString.size()-1){
                        add(keyAcc, valueAcc);
                    }
                }
            }
            std::string getValue(std::string key){
                if(query.count(key) == 1){
                    return query.at(key);
                }
                else return "";
            }

            std::string getText(){
                return queryString;
            }

            void print(){
                for(auto item :  query){
                    LogColors::print(LogColors::YELLOW, item.first, ":", item.second);
                }
            }
        };
    private:
        Method method;
        std::string url;
        Query* query;
        Query* body;
        std::unordered_map<std::string, std::string> headerFields;
        bool isBadRequestBool;
    public:
        Request(char* request_str){
            isBadRequestBool = false;
            LogColors::print(LogColors::YELLOW, "___________________________________");
            LogColors::print(LogColors::MAGENTA, request_str);
            LogColors::print(LogColors::YELLOW, "___________________________________");
            request_parser(request_str);
        }

        void request_parser(std::string request_str){
            std::vector<std::string> requestArr = stringMethods::stringSplit(request_str, "\n");
            parseRequestLine(requestArr[0]);
            bool inBody = false;;
            std::string bodyString;
            for(int i = 1; i < requestArr.size(); i++){
                // LogColors::print(LogColors::YELLOW, "++++++++++++++++++++++++++++++++++++");
                if(requestArr[i].compare("\r") == 0 || requestArr[i].compare("") == 0){
                    inBody = true;
                    continue;
                }

                if(!inBody){
                    std::vector<std::string> headerRow = stringSplitAtFirst(requestArr[i], ":");
                    std::string value = headerRow[1];
                    if(value.size() > 0 && value[0] == ' '){
                        value.erase(value.begin(), value.begin()+1);
                    }
                    headerFields[headerRow[0]] = value;
                }
                else{
                    bodyString += requestArr[i];
                }
                // LogColors::print(LogColors::RED, "Key: ", headerRow[0]);
                // LogColors::print(LogColors::GREEN, "Value: ", headerRow[1]);
                // LogColors::print(LogColors::BLUE, ".");
                // LogColors::print(LogColors::YELLOW, "++++++++++++++++++++++++++++++++++++");
            }
            this->body = new Query(bodyString);
        }

        void parseRequestLine(std::string request_str){
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
            if(request_str[i] == '?'){
                std::string queryStr;
                i++;
                while (request_str[i] != ' '){
                    queryStr += request_str[i];
                    i++;
                }
                this->query = new Query(queryStr);
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

        Query* getQuery(){
            return query;
        }

        Query* getBody(){
            return body;
        }

        std::string getHeader(std::string key){
            if(headerFields.count(key) == 1){
                return headerFields.at(key);
            }
            else return "";
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