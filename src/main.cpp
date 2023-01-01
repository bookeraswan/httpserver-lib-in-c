#include "lib/Server.h"
#include "./lib/Router.h"
#include "./lib/LogColors.h"

int main(){
    Router* router = new Router();
    
    router->routePublicDirectory("./public");

    router->get("/", [](Request* req, Response* res){
        res->send_file("./public/index.html");
    });

    router->get("/third", [](Request* req, Response* res){
        res->send_file("./public/second.html");
    });

    new Server(router, 2000);
}