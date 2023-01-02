#pragma once
#include <string>
#include "../str.h"
#include "MapWraper.hpp"
#include "Cookie.hpp"

class Header : public MapWrapper{
    private:
        Cookie* cookie;
    public:
        Header(std::string rawData): MapWrapper(rawData){}
        void parse(){
            for(std::string line : stringMethods::stringSplit(getText(), "\n")){
                if(line.compare("\r") == 0 || line.compare("") == 0){
                    break;
                }
                std::vector<std::string> headerRow = stringMethods::stringSplitAtFirst(line, ":");
                std::string key = stringMethods::strip(headerRow[0]);
                std::string value = stringMethods::strip(headerRow[1]);
                addEntry(key, value);
            }
            cookie = new Cookie(getValue("Cookie"));
            cookie->parse();
        }

        Cookie* getCookie(){
            return cookie;
        }
};