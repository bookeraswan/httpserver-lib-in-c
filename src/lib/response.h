#ifndef RESPONSE_LIB
#define RESPONSE_LIB
#include "str.h"
#include <stdlib.h>

#define FILE_LINE_SIZE 1024

typedef struct{
    int status;
    str message;
}Response;


void send_txt(Response* response, char* message){
    str_append(&response->message, message);
}



void send_file(Response* response, const char* file_name){
    FILE * fp = fopen(file_name, "r");
    char line[FILE_LINE_SIZE];
    while(!feof(fp)){
        memset(line, 0, FILE_LINE_SIZE);
        fgets(line, FILE_LINE_SIZE, fp);
        str_append(&response->message, line);
    }
    fclose(fp);
}

#endif
