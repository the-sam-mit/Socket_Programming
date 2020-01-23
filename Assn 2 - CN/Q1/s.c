#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8080
#define MAXLINE 1024

int main(){
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    char msg[2], msg2[2];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t cli_len = sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, &cli_len) <0){
        perror("error receiving msg");
        exit(EXIT_FAILURE);
    }
    printf("Client message received: %s\n", msg);
    if(msg[0] == 'a') msg[0]='z';
    else if(msg[0] == 'A') msg[0]='Z';
    else msg[0] = msg[0]-1;

    if(recvfrom(sockfd, msg2, sizeof(msg2), 0, (struct sockaddr *) &cli_addr, &cli_len) <0){
        perror("error receiving msg");
        exit(EXIT_FAILURE);
    }

    if(sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, cli_len) <0){
        perror("error sending msg");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");
    close(sockfd);
    return 0;
}
