#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
int main(){
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);



    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    char s_msg[256];
    while(1){
        printf("Client: ");
        fgets(s_msg, sizeof(s_msg), stdin);
        if(strncmp(s_msg, "bye", 3)==0) break;
        if(send(sockfd, &s_msg, sizeof(s_msg), 0)<0){
            perror("send failed");
            exit(EXIT_FAILURE);
        }

        if(recv(sockfd, s_msg, sizeof(s_msg), 0)<0){
            perror("rcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Server: %s", s_msg);
    }
    close(sockfd);
}