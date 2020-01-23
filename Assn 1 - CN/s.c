#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#define PORT 8080

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr, cli_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    char s_msg[256];

    socklen_t cli_len = sizeof(cli_addr);
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if(listen(sockfd, 5)<0){
	    perror("listen failed");
        exit(EXIT_FAILURE);
    }
    int clifd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    while(1){
    	if(recv(clifd, s_msg, sizeof(s_msg), 0)<0){
            perror("recv failed");
            exit(EXIT_FAILURE);
        }
        printf("Client: %s\n", s_msg);
        printf("Server: ");

        fgets(s_msg, sizeof(s_msg), stdin);
        if(strncmp(s_msg, "bye", 3)==0) break;
        if(send(clifd, s_msg, sizeof(s_msg), 0)<0){
            perror("send failed");
            exit(EXIT_FAILURE);
        }
    }
    close(clifd);
}