#pragma once
#include <functional>
#include "Request.h"
#include "Response.h"
#include "LogColors.h"
#include "FileSystemTraversal.h"

class Router{
    private:
        std::unordered_map<std::string, std::function <void (Request*, Response*)>> routes;
    public:
        Router(){

        }
        void router(Request* req, Response* res){
            try{
                routes.at(req->getMethodString()+" "+req->getUrl())(req, res);
            }
            catch(const std::out_of_range& oor){ // This will occur if the route does not exist
                res->send_txt("<h1>404 Route \"" + req->getUrl() + "\" not found :(</h1>");
            };
        }

        void get(std::string url, std::function <void (Request*, Response*)> logic){
            routes["GET " + url] = logic;
        }

        void post(std::string url, std::function <void (Request*, Response*)> logic){
            routes["POST " + url] = logic;
        }

        void put(std::string url, std::function <void (Request*, Response*)> logic){
            routes["PUT " + url] = logic;
        }

        void del(std::string url, std::function <void (Request*, Response*)> logic){
            routes["DELETE " + url] = logic;
        }

        void routeFile(std::string url, std::string fileName){
            get(url, [fileName](Request* req, Response* res){
                res->send_file(fileName);
            });
        }

        void routePublicDirectory(std::string path){
            using namespace std;
            for(string fileName : FileSystemTraversal::filesUnderDirectory("./public")){
                string route = fileName;
                route.erase(route.begin(), route.begin()+1);
                routeFile(route, fileName);
            }
        }
};
