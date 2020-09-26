#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <time.h> 
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define PORT 8180

int main(int argc, char *argv[])
{
    int fd1 = 0, fd2 = 0;
    struct sockaddr_in serv_addr; 
    char sbuffer[1025];
    time_t ticks; 
    fd1 = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sbuffer, '0', sizeof(sbuffer)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT); 
    bind(fd1, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(fd1, 10); 
    while(1){
        fd2 = accept(fd1, (struct sockaddr*)NULL, NULL); 
        ticks = time(NULL);
        snprintf(sbuffer, sizeof(sbuffer), "%.24s\r\n", ctime(&ticks));
        write(fd2, sbuffer, strlen(sbuffer)); 
        close(fd2);
        sleep(1);
    }
}