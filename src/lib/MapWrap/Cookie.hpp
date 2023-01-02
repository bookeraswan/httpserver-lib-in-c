#pragma once
#include <string>
#include "../str.h"
#include "MapWraper.hpp"

class Cookie : public MapWrapper{
    public:
        Cookie(std::string rawData): MapWrapper(rawData){}

        void parse(){
            std::vector<std::string> keyValueStrings = stringMethods::stringSplit(getText(), "; ");
            for(std::string keyValueString : keyValueStrings){
                std::string keyValueStringStriped = stringMethods::strip(keyValueString);
                std::vector<std::string> keyValuePair = stringMethods::stringSplitAtFirst(keyValueStringStriped, "=");
                if(keyValuePair.size() > 1){
                    addEntry(keyValuePair[0], keyValuePair[1]);
                }
            }
        }
};