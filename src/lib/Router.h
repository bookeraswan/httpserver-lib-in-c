#pragma once
#include <functional>
#include "request.h"
#include "response.h"
#include "LogColors.h"
#include "FileSystemTraversal.h"

class Router{
    private:
        std::unordered_map<std::string, std::function <void (Request, Response*)>> routes;
    public:
        enum Method{
            GET,
            POST,
            PUT,
            DELETE
        };
        Router(){

        }
        void router(Request req, Response* res){
            try{
                std::string m = req.method;
                std::string u = req.url;
                std::cout << m+" "+u << std::endl;
                routes.at(m+" "+u)(req, res);
            }
            catch(const std::out_of_range& oor){ // This will occur if the route does not exist
                char message[50] = "<h1>404 Route \"";
                const char* endofmessage = "\" not found :(</h1>";
                strcat(message, req.url);
                strcat(message, endofmessage);
                send_txt(res, message);
            };
        }

        // void createRoute(Method method, std::string url, std::function <void (Request, Response*)> logic){
        //     std::string methodStr;
        //     switch (method)
        //     {
        //     case GET:
        //         methodStr = "GET";
        //         break;
        //     case POST:
        //         methodStr = "POST";
        //         break;
        //     case PUT:
        //         methodStr = "PUT";
        //         break;
        //     case DELETE:
        //         methodStr = "DELETE";
        //         break;
        //     default:
        //         methodStr = "GET";
        //         break;
        //     }

        //     routes[methodStr + " " + url] = logic;
            
        // }

        void get(std::string url, std::function <void (Request, Response*)> logic){
            routes["GET " + url] = logic;
        }

        void post(std::string url, std::function <void (Request, Response*)> logic){
            routes["POST " + url] = logic;
        }

        void put(std::string url, std::function <void (Request, Response*)> logic){
            routes["PUT " + url] = logic;
        }

        void del(std::string url, std::function <void (Request, Response*)> logic){
            routes["DELETE " + url] = logic;
        }

        void routeFile(std::string url, std::string fileName){
            get(url, [fileName](Request req, Response* res){
                send_file(res, fileName.c_str());
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
