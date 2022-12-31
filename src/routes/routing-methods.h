#pragma once
#include <string.h>

int request_count = 0;

void route_root(Request req, Response* res){
    send_file(res, "./public/index.html");
}

void counter(Request req, Response* res){
    char sendable[34];
    sprintf(sendable, "<h1><h1>count: %d</h1></h1>", request_count);
    send_txt(res, sendable);
    request_count += 1;
}

void route_404 (Request req, Response* res){
    char message[50] = "<h1>404 Route \"";
    const char* endofmessage = "\" not found :(</h1>";
    strcat(message, req.url);
    strcat(message, endofmessage);
    send_txt(res, message);
}