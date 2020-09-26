#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 8180

int main(int argc, char *argv[])
{
    int fd1 = 0, n = 0;
    char buffer[1024];
    struct sockaddr_in s_address; 
    if(argc != 2){
        printf("\n Usage: Enter the IP address also as second argument\n");
        return 1;
    } 
    memset(buffer, '0',sizeof(buffer));
    if((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Error\n");
        return 1;
    } 
    memset(&s_address, '0', sizeof(s_address)); 
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(PORT); 
    if(inet_pton(AF_INET, argv[1], &s_address.sin_addr)<=0){
        printf("\n Error\n");
        return 1;
    } 
    if( connect(fd1, (struct sockaddr *)&s_address, sizeof(s_address)) < 0){
       printf("\n Error\n");
       return 1;
    } 
    while ( (n = read(fd1, buffer, sizeof(buffer)-1)) > 0){
        buffer[n] = 0;
        if(fputs(buffer, stdout) == EOF){
            printf("\n Error\n");
        }
    } 
    return 0;
}