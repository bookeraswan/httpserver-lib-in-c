#ifndef DYNAMIC_STR
#define DYNAMIC_STR
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_set>

typedef char* str;

str str_create(const char *chararr){
    int char_count = 0;
    while(chararr[char_count] != 0){
        char_count++;
    }
    char* new_str = (char*)calloc((char_count+1),sizeof(char));
    for(int i = 0; i <= char_count; i++){
        *(new_str+i) = chararr[i];
    }
    return new_str;
}

void str_append(str* original_string, char* added_string){
    int new_total_length = 0;
    int original_length  = 0;
    int added_length     = 0;
    while((*original_string)[original_length] != 0){
        new_total_length++;
        original_length++;
    }
    while(added_string[added_length] != 0){
        new_total_length++;
        added_length++;
    }
    *original_string = (str)realloc((void*)*original_string, (new_total_length+1)*sizeof(char));
    for(int i = 0; i <= added_length; i++){
        (*original_string)[original_length+i] = added_string[i];
    }
}

int str_get_idx(const char search[], size_t length, char raw_string[]){
    char buff;
    int i = 0;
    do{
        if(strncmp(&raw_string[i], search, length) == 0) return i;
        i++;
    }while(raw_string[i] != 0);
    return -1;
}

namespace stringMethods{

    std::string stringReplaceAll(std::string original, std::string from, std::string to){
        std::string output;
        for(int i = 0; i < original.size(); i++){
            bool found = true;
            int j;
            for(j = 0; j < from.size(); j++){
                if(i+j >= original.size()){
                    break;
                }
                if(original[i+j] != from[j]){
                    found = false;
                }
            }
            if(found){
                output += to;
                i += j-1;
            }
            else output += original[i];
        }
        return output;
    }

    std::vector<std::string> stringSplitAtFirst(std::string s, std::string delimiter){
        std::vector<std::string> output = std::vector<std::string>();
        size_t pos = s.find(delimiter);
        std::string token = s.substr(0, pos);
        output.push_back(token);
        s.erase(0, pos + delimiter.length());
        output.push_back(s);
        return output;
    }

    std::vector<std::string> stringSplit(std::string s, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> output = std::vector<std::string>();
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            output.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        output.push_back(s);
        return output;
    }

    bool isSpaceTypeChar(char c){
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    std::string stripLeft(std::string s){
        std::string strn = s;
        while(strn.size() > 0 && isSpaceTypeChar(strn[0])){
            strn.erase(strn.begin(), strn.begin() + 1);
        }
        return strn;
    }

    std::string stripRight(std::string s){
        std::string strn = s;
        while(strn.size() > 0 && isSpaceTypeChar(strn[strn.size()-1])){
            strn.erase(strn.end()-1, strn.end());
        }
        return strn;
    }

    std::string strip(std::string s){
        std::string strn = stripRight(s);
        return stripLeft(strn);
    }

    std::string toLowerCase(std::string s){
        std::string strn;
        for(char chr : s){
            strn += tolower(chr);
        }
        return strn;
    }

}

#endif