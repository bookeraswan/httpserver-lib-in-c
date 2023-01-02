#pragma once

#include "str.h"
#include <stdlib.h>
#include <string>
#include <unordered_set>

#define FILE_LINE_SIZE 1024


class Response{
    private:
        std::string status;
        std::string message;
        std::string headers;
    public:
        std::byte* fileBytes;
        int size;

        Response(){
            this->status = "200 OK";
            this->fileBytes = nullptr;
            this->size = 0;
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

        void addHeader(std::string key, std::string value){
            headers += key + ": " + value + "\n";
        }

        std::string getHeaders(){
            if(headers.size() != 0){
                headers = "\n" + headers;
                headers.erase(headers.end()-1, headers.end());
            }
            return headers;
        }

        void redirect(std::string url){
            this->status = "303 See Other";
            addHeader("Location", url);
        }

        void send_txt(std::string message){
            this->message += message;
        }

        size_t file_size(const char* file_path) {
            FILE* fin = fopen(file_path, "rb");
            if (fin == NULL) {
                printf("open %s failed.", file_path);
                exit(0);
            }

            fseek(fin, 0L, SEEK_END);
            size_t size = ftell(fin);
            fclose(fin);
            return size;
        }

        void send_file(std::string file_name){
            this->size = file_size(file_name.c_str());
            addHeader("Content-Type", contentType(file_name));
            addHeader("Content-length", std::to_string(size));
            this->fileBytes = new std::byte[size];
            FILE * fp = fopen(file_name.c_str(), "r");
            for(int i = 0; i < size; i++){
                this->fileBytes[i] = (std::byte)fgetc(fp);
            }
        }

        std::string fileExt(std::string file_name){
            std::vector<std::string> fileParts = stringMethods::stringSplit(file_name, ".");
            return fileParts[fileParts.size()-1];
        }

        std::string contentType(std::string file_name){
            std::string ext = stringMethods::toLowerCase(fileExt(file_name));
            std::string type;
            std::unordered_set<std::string> application;
            std::unordered_set<std::string> audio;
            std::unordered_set<std::string> image;
            std::unordered_set<std::string> video;
            std::unordered_set<std::string> text;
            application.insert("json");
            application.insert("ogg");
            application.insert("pdf");
            application.insert("js"); // javascript
            application.insert("xml");
            audio.insert("mpeg");
            audio.insert("mp3");
            audio.insert("wav"); // x-wav
            image.insert("gif");
            image.insert("jpeg");
            image.insert("jpg");
            image.insert("tiff");
            image.insert("svg"); //
            video.insert("mpeg");
            video.insert("mp4");
            video.insert("webm");
            text.insert("css");
            text.insert("csv");
            text.insert("html");
            text.insert("txt"); // plain
            text.insert("xml");
            if(application.count(ext) == 1){
                if(ext.compare("js") == 0){
                    ext = "javascript";
                }
                type = "application/" + ext;
            }
            else if(audio.count(ext) == 1){
                if(ext.compare("wav") == 0){
                    ext = "x-wav";
                }
                type = "audio/" + ext;
            }
            else if(video.count(ext) == 1){
                type = "audio/" + ext;
            }
            else if(text.count(ext) == 1){
                if(ext.compare("txt") == 0){
                    ext = "plain";
                }
                type = "text/" + ext;
            }
            else{
                type = "text/plain";
            }
            return type;
        }

        ~Response(){
            if(fileBytes != nullptr){
                delete fileBytes;
            }
        }
};
