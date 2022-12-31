#include "lib/Server.h"
#include "./lib/Router.h"
#include "./lib/LogColors.h"
int main(){
    Router* router = new Router();

    router->get("/", [](Request req, Response* res){
        send_file(res, "./public/index.html");
    });

    router->get("/third", [](Request req, Response* res){
        send_file(res, "./public/second.html");
    });

    new Server(router, 8080);
    // request_parser("GET / HTTP/1.1\nHost: localhost:2000\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate\nConnection: keep-alive\nUpgrade-Insecure-Requests: 1\n");
}