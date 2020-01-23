#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#define PORT 8080
#define MAXLINE 1024

int main(){
    int sockfd;
    char s_msg[256], c_msg[256];
    char f_buffer[10000];
    struct sockaddr_in cli_addr, serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t cli_len = sizeof(cli_addr);

    FILE *fileptr;
    fileptr = fopen("input.txt", "r");
    if(fileptr==NULL){
        printf("error");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(sockfd,3) <0){
        perror("error listening msg");
        exit(EXIT_FAILURE);
    }
    
    int cli_sock = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

    char *token;
    int flg=0;
    int f2=0;

    recv(cli_sock, s_msg, sizeof(s_msg), 0);
    printf("%s\n", s_msg);

    while(fgets(f_buffer, 10000, (FILE *)fileptr)){
        token = strtok(f_buffer, " ");
        while(token!=NULL){
            if(flg==1){
                strcpy(c_msg, token);
                f2=1;
                flg=0;
                // printf("%d\n", );
            }
            if(strcmp(token, s_msg)==0) flg=1;
            token = strtok(NULL, " ");
        }
    }
    if(f2==0){
        strcpy(c_msg, "Not found in directory.\n");
    }
    send(cli_sock, c_msg, sizeof(c_msg), 0);
    close(sockfd);

}
