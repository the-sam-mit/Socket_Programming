#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8080
int main(){
    int sockfd;
    struct sockaddr_in cli_addr;

    char c_msg[256], s_msg[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t cli_len = sizeof(cli_addr);


    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    cli_addr.sin_port = htons(PORT);

    if(connect(sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr))<0){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    char query[256];
    printf("Enter a number\n");
    scanf("%s", query);

    if(send(sockfd, query, sizeof(query), 0)<0){
        perror("send failed");
        exit(EXIT_FAILURE);
    }

    if(recv(sockfd, query, sizeof(query), 0)<0){
        perror("send failed");
        exit(EXIT_FAILURE);
    }

    printf("Server sent: %s\n", query);
    close(sockfd);
}