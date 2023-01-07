#include "common.h"
#include "str.h"
#include "LogColors.h"
#include "Request.h"
#include "Response.h"
#include "Router.h"

#define MAXLINE 4096
#define SA struct sockaddr

class Server{
private:
    int port;
public:

    Server(Router* router, int port){
        this->port = port;
        createServer(router);
    }
private:
void init_sockaddr_in(struct sockaddr_in* servaddr){
    bzero(servaddr, sizeof(*servaddr));
    servaddr->sin_family      = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port        = htons(port);
}

void bind_and_listen(int listenfd, struct sockaddr_in  servaddr){
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    listen(listenfd, 12);
    printf("Listening on port %d\n\n", port);
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

std::string get_request_data(int connection_socket){
        std::string request_str;
        char recvline[MAXLINE+1];
        memset(recvline, 0, MAXLINE);
        int n = read(connection_socket, recvline, MAXLINE-1);
        while (n > 0 && !stringMethods::contains(request_str, "\r")){
            request_str += recvline;
        }
        return request_str;
}

void infinite_server_loop(int listenfd, Router* router){
    int connection_socket;
    char buff[MAXLINE+1];
    while(1){
        connection_socket = accept(listenfd, (SA*)NULL, NULL);
        printf("\t----REQUEST BEGINNING----\n\n");
        std::string request_str   = get_request_data(connection_socket).c_str();
        if(request_str.size() == 0) continue;
        Request* request   = new Request(request_str);
        if(request->isBadRequest()){
            snprintf(buff, sizeof(buff), "HTTP/1.1 400 Bad Request\r\n\r\n");
            write(connection_socket, buff, strlen(buff));
            printf("\n\t----REQUEST END, Request Was Bad----\n\n");
            close(connection_socket);
            break;
        }
        Response* response = new Response();
        router->router(request, response);
        snprintf(buff, sizeof(buff), "HTTP/1.1 %s%s\r\n\r\n%s", response->getStatus().c_str(), response->getHeaders().c_str(), response->getMessage().c_str());
        write(connection_socket, buff, strlen(buff));
        write(connection_socket, response->fileBytes, response->size);
        delete response;
        printf("\n\t----REQUEST END----\n\n");
        close(connection_socket);
    }
}

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