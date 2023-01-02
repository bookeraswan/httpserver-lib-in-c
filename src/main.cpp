#include "lib/Server.h"
#include "./lib/Router.h"
#include "./lib/LogColors.h"
#include "./lib/hashing/Auth.h"

int main(){
    std::unordered_map<std::string, std::string> users;
    std::unordered_map<std::string, std::string> sessions;

    Router* router = new Router();
    Auth* auth = new Auth("/me", "/me");
    
    router->routePublicDirectory("./public");

    router->get("/", [](Request* req, Response* res){
        res->send_file("./public/index.html");
    });

    router->routeFile("/signup", "./public/signup.html");
    router->routeFile("/login", "./public/login.html");

    router->post("/signup", [&auth](Request* req, Response* res){
        auth->attemptSignup(req, res);
    });

    router->post("/login", [&auth](Request* req, Response* res){
        auth->attemptLogin(req, res);
    });

    router->get("/third", [](Request* req, Response* res){
        req->getQuery()->printContense();
        res->send_file("./public/second.html");
    });

    router->get("/me", [&auth](Request* req, Response* res){
        if(!auth->isLoggedin(req)){
            res->send_txt("<h1>Error: Login or Signup</h1>");
            return;
        }
        res->send_txt("<h1>Hi "+auth->getSessionUser(req)+", you are logged in.</h1>");
    });
    
    new Server(router, 8088);
}
