#include "lib/Server.h"
#include "./lib/Router.h"
#include "./lib/LogColors.h"

int main(){
    std::unordered_map<std::string, std::string> users;
    std::unordered_map<std::string, std::string> sessions;

    Router* router = new Router();
    
    router->routePublicDirectory("./public");

    router->get("/", [](Request* req, Response* res){
        res->send_file("./public/index.html");
    });

    router->routeFile("/signup", "./public/signup.html");
    router->routeFile("/login", "./public/login.html");

    router->post("/signup", [&users, &sessions](Request* req, Response* res){
        req->getBody()->parse();
        std::string u = req->getBody()->getValue("username");
        std::string p = req->getBody()->getValue("password");
        users[u] = p;
        sessions[u+p] = u;
        // res->redirect("/later");
        res->send_txt("<script>document.cookie = 'unsession="+u+p+"';window.location = '/me';</script>");
    });

    router->post("/login", [&users, &sessions](Request* req, Response* res){
        req->getBody()->parse();
        std::string u = req->getBody()->getValue("username");
        std::string p = req->getBody()->getValue("password");
        if(users.count(u) == 1){
            if(p == users.at(u)){
                res->send_txt("<script>document.cookie = 'unsession="+u+p+"';window.location = '/me';</script>");
                return;
            }
        }
        res->redirect("/login");
    });

    router->get("/third", [](Request* req, Response* res){
        req->getQuery()->printContense();
        res->send_file("./public/second.html");
    });

    router->get("/me", [&sessions](Request* req, Response* res){
        std::string session = req->getCookie()->getValue("unsession");
        if(session != ""){
            if(sessions.count(session) == 1){
                res->send_txt("<h1>Hi "+sessions.at(session)+", you are logged in.</h1>");
                return;
            }
        }
        res->send_txt("<h1>Error: Login or Signup</h1>");
    });
    
    new Server(router, 8080);
}