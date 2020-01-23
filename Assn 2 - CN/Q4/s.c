#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8080
#define MAXLINE 1024

struct pkt{
    char c[2];
    int i;
    float f;
};

int main(){
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    struct pkt msg, msg2;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t cli_len = sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, &cli_len) <0){
        perror("error receiving msg");
        exit(EXIT_FAILURE);
    }
    printf("Client1 message received: %d\n", msg.i);
    printf("Client1 message received: %s\n", msg.c);
    printf("Client1 message received: %f\n", msg.f);
    
    msg.f = (msg.f*1.5);
    msg.i = (msg.i+3);
    msg.c[0] = (msg.c[0]+1);

    // printf("Client2 message received: %d\n", msg.i);
    // printf("Client2 message received: %c\n", msg.c);
    // printf("Client2 message received: %f\n", msg.f);

    if(recvfrom(sockfd, &msg2, sizeof(msg2), 0, (struct sockaddr *) &cli_addr, &cli_len) <0){
        perror("error receiving msg");
        exit(EXIT_FAILURE);
    }

    if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, cli_len) <0){
        perror("error sending msg");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");
    close(sockfd);
    return 0;
}
