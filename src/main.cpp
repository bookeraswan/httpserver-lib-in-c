#include "lib/Server.h"
#include "./lib/Router.h"
#include "./lib/LogColors.h"

int main(){
    Router* router = new Router();
    
    router->routePublicDirectory("./public");

    router->get("/", [](Request* req, Response* res){
        res->send_file("./public/index.html");
    });

    router->post("/signup", [](Request* req, Response* res){
        req->getBody()->parse();
        LogColors::print(LogColors::BLUE, "Query");
        req->getQuery()->printContense();
        LogColors::print(LogColors::BLUE, "Header");
        req->getHeader()->printContense();
        LogColors::print(LogColors::BLUE, "Body");
        req->getBody()->printContense();
        LogColors::print(LogColors::BLUE, "Cookies");
        req->getCookie()->printContense();
        res->send_txt("Hello " + req->getBody()->getValue("username"));
    });

    router->get("/third", [](Request* req, Response* res){
        req->getQuery()->printContense();
        res->send_file("./public/second.html");
    });

    new Server(router, 8083);
}