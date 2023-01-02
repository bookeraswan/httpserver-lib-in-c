#pragma once
#include <string>
#include <unordered_map>
#include "../str.h"
#include "../LogColors.h"

class MapWrapper{
    private:
        std::unordered_map<std::string, std::string> dataMap;
        std::string rawData;
    protected:
        void addEntry(std::string key, std::string value){
            dataMap[key] = value;
        }
    public:
        MapWrapper(std::string rawData){
            this->rawData = stringMethods::strip(rawData);
        }

        virtual void parse(){};

        std::string getValue(std::string key){
            if(dataMap.count(key) == 1){
                return dataMap.at(key);
            }
            else return "";
        }

        std::string getText(){
            return rawData;
        }

        virtual bool isEmpty(){
            return dataMap.size() == 0;
        }

        void printContense(){
            LogColors::print(LogColors::MAGENTA, "{");
            for(auto item :  dataMap){
                LogColors::print(LogColors::GREEN, "\t", item.first, ": ", item.second, ",");
            }
            LogColors::print(LogColors::MAGENTA, "}");
        }
};