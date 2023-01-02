#pragma once

#include <string>
#include <unordered_map>
#include "sha256.h"
#include "../Request.h"
#include "../Response.h"


class Auth{
    private:
        std::string signupRedirectRoute;
        std::string loginRedirectRoute;
        std::unordered_map<std::string, std::string> users;
        std::unordered_map<std::string, std::string> sessions;
    public:

        Auth(std::string signupRedirectRoute, std::string loginRedirectRoute){
            this->signupRedirectRoute = signupRedirectRoute;
            this->loginRedirectRoute = loginRedirectRoute;
        }

        bool attemptSignup(Request* req, Response* res){
            req->getBody()->parse();
            std::string username = req->getBody()->getValue("username");
            std::string password = req->getBody()->getValue("password");
            if(isInvalidUsername(username) || isInvalidPassword(password) || usernameExists(username)){
                res->redirect(req->getUrl());
                return false;
            }
            std::string sessionHash = generateSession(req);
            users[username] = SHA256(password.c_str());
            sessions[sessionHash] = username;
            res->send_txt("<script>"); 
            res->send_txt("document.cookie = 'unsession="+sessionHash+"';");
            res->send_txt("window.location = '"+signupRedirectRoute+"';");
            res->send_txt("</script>");
            return true;
        }

        bool attemptLogin(Request* req, Response* res){
            req->getBody()->parse();
            std::string username = req->getBody()->getValue("username");
            std::string password = req->getBody()->getValue("password");
            LogColors::print(LogColors::WHITE, username, password);
            LogColors::print(LogColors::WHITE, isInvalidUsername(username),isInvalidPassword(password),!usernameMatchesPassword(username, password));
            if(isInvalidUsername(username)
                ||isInvalidPassword(password)
                || !usernameMatchesPassword(username, password)){
                res->redirect(req->getUrl());
                return false;
            }
            std::string sessionHash = generateSession(req);
            sessions[sessionHash] = username;
            res->send_txt("<script>"); 
            res->send_txt("document.cookie = 'unsession="+sessionHash+"';");
            res->send_txt("window.location = '"+loginRedirectRoute+"';");
            res->send_txt("</script>");
            return true;
        }

        bool isLoggedin(Request* req){
            return sessionExists(req->getCookie()->getValue("unsession"));
        }

        bool isInvalidUsername(std::string username){
            return username.size() == 0 || username.size() > 30;
        }

        bool isInvalidPassword(std::string password){
            return password.size() == 0 || password.size() > 30;
        }

        std::string getSessionUser(Request* req){
            std::string session = req->getCookie()->getValue("unsession");
            if(sessionExists(session)){
                std::string username = sessions.at(session);
                if(!usernameExists(username)){
                    sessions.erase(session);
                    return "";
                }
                return username;
            }
            return "";
        }

        bool usernameExists(std::string username){
            return users.count(username) == 1;
        }

        bool usernameMatchesPassword(std::string username, std::string password){
            return usernameExists(username) && SHA256(password.c_str()) == users.at(username);
        }

        bool sessionExists(std::string session){
            return session.size() == 64 && sessions.count(session) == 1;
        }

        std::string generateSession(Request* req){
            return SHA256((req->getHeader()->getText() + std::to_string(rand())).c_str());
        }
};
