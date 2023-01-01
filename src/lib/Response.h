#pragma once

#include "str.h"
#include <stdlib.h>
#include <string>

#define FILE_LINE_SIZE 1024


class Response{
    private:
        std::string status;
        std::string message;
    public:

        Response(){
            this->status = "200 OK";
        }

        std::string getMessage(){
            return message;
        }

        std::string getStatus(){
            return status;
        }

        void setStatus(int status){
            if(status == 200){
                this->status = "200 OK";
            }
            if(status == 404){
                this->status = "404 Not Found";
            }
        }

        void send_txt(std::string message){
            this->message += message;
        }

        void send_file(std::string file_name){
            FILE * fp = fopen(file_name.c_str(), "r");
            char line[FILE_LINE_SIZE];
            while(!feof(fp)){
                memset(line, 0, FILE_LINE_SIZE);
                fgets(line, FILE_LINE_SIZE, fp);
                send_txt(line);
            }
            fclose(fp);
        }
};
