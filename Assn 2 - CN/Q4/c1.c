#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8080

struct pkt{
    char c[2];
    int i;
    float f;
};

int main(){
    struct pkt msg;
     int clifd;
     struct sockaddr_in cli_addr;
     socklen_t cli_len = sizeof(cli_addr);
     clifd = socket(AF_INET, SOCK_DGRAM, 0);

     cli_addr.sin_family = AF_INET;
     cli_addr.sin_addr.s_addr = INADDR_ANY;
     cli_addr.sin_port = htons(PORT);

     printf("Enter an integer, character and float to send\n");
     scanf("%d", &msg.i);
     scanf("%s", msg.c);
     scanf("%f", &msg.f);

    if(sendto(clifd, &msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, cli_len) <0){
        perror("error sending msg");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");
    close(clifd);
}