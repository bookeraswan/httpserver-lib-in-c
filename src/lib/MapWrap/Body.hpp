#pragma once
#include <string>
#include "../str.h"
#include "Query.hpp"

class Body : public Query{
    public:
        Body(std::string rawData): Query(rawData){}
        
        bool isEmpty(){
            return getText().size() == 0;
        }
};