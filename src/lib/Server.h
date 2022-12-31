#include "common.h"
#include "str.h"
#include "request.h"
#include "response.h"
#include "../routes/Router.h"
// #include "printf_colors.h"



#define SERVER_PORT 2000
#define MAXLINE 4096
#define SA struct sockaddr

class Server{
public:
    // Server(void (*router)(Request, Response*)){
    //     createServer(router);
    // }

    Server(Router* router){
        createServer(router);
    }
private:
void init_sockaddr_in(struct sockaddr_in* servaddr){
    bzero(servaddr, sizeof(*servaddr));
    servaddr->sin_family      = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port        = htons(SERVER_PORT);
}

void bind_and_listen(int listenfd, struct sockaddr_in  servaddr){
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    listen(listenfd, 12);
    printf("Listening on port %d\n\n", SERVER_PORT);
}

int get_content_length(char line[]){
    char value[5];
    int i = str_get_idx("Content-Length: ", 16, line) + 15;
    if(i == -1) return 0;
    int value_start = i;
    do{
        value[i-value_start] = line[i];
        i++;
    }while(line[i] != '\n' && (i-value_start) < 5);
    return atoi(value);
}

str get_request_data(int connection_socket){
        str request_str = str_create("");
        char recvline[MAXLINE+1];
        memset(recvline, 0, MAXLINE);
        int n = read(connection_socket, recvline, MAXLINE-1);
        str_append(&request_str, recvline);
        //printf_color1(P_BLU, "%s", request_str);
        return request_str;
}

void infinite_server_loop(int listenfd, Router* router){
    int connection_socket;
    char buff[MAXLINE+1];
    while(1){
        connection_socket = accept(listenfd, (SA*)NULL, NULL);
        printf("\t----REQUEST BEGINNING----\n\n");
        str request_str   = get_request_data(connection_socket);
        if(strlen(request_str) == 0) continue;
        Request request   = request_parser(request_str);
        free(request_str);
        //printf_color2(P_GRN, "{method: \"%s\", url: \"%s\"}\n", request.method, request.url);
        Response response;
        response.message = str_create("");
        router->router(request, &response);
        snprintf(buff, sizeof(buff), "HTTP/1.1 200 OK\r\n\r\n%s", response.message);
        write(connection_socket, buff, strlen(buff));
        free(response.message);
        printf("\n\t----REQUEST END----\n\n");
        close(connection_socket);
    }
}



// void createServer(void (*router)(Request, Response*)){
//     int listenfd;
//     struct sockaddr_in  servaddr;
//     listenfd = socket(AF_INET, SOCK_STREAM, 0);
//     init_sockaddr_in(&servaddr);
//     bind_and_listen(listenfd, servaddr);
//     infinite_server_loop(listenfd, router);
//     close(listenfd);
// }

void createServer(Router* router){
    int listenfd;
    struct sockaddr_in  servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    init_sockaddr_in(&servaddr);
    bind_and_listen(listenfd, servaddr);
    infinite_server_loop(listenfd, router);
    close(listenfd);
}

};