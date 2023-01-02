#pragma once
#include <string>
#include "../str.h"
#include "MapWraper.hpp"

class Query : public MapWrapper{
    public:
        Query(std::string rawData): MapWrapper(rawData){}
        void parse(){
            std::string keyAcc;
            std::string valueAcc;
            bool isKey = true;
            for(int i = 0; i < getText().size(); i++){
                if(getText()[i] == '&'){
                    addEntry(stringMethods::stringReplaceAll(keyAcc, "%20", " "), stringMethods::stringReplaceAll(valueAcc, "%20", " "));
                    keyAcc = "";
                    valueAcc = "";
                    isKey = true;
                }
                else if(getText()[i] == '='){
                    isKey = false;
                }
                else if(isKey){
                    keyAcc += getText()[i];
                }
                else{
                    valueAcc += getText()[i];
                }

                if(i == getText().size()-1){
                    addEntry(stringMethods::stringReplaceAll(keyAcc, "%20", " "), stringMethods::stringReplaceAll(valueAcc, "%20", " "));
                }
            }
        }
};