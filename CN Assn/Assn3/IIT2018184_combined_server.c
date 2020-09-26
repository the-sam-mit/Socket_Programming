#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>
#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#define PORT 8180 
#define MAXLINE 1024

int func(char * hostname , char* ip){
  struct hostent *he;
  struct in_addr **addr_list;
  int i;
  if ( (he = gethostbyname( hostname ) ) == NULL) {
    herror("gethostbyname");
    return 1;
  }
  addr_list = (struct in_addr **) he->h_addr_list;
  for(i = 0; addr_list[i] != NULL; i++) {
    strcpy(ip , inet_ntoa(*addr_list[i]) );
    return 0;
  }  
  return 1;
}
int max(int x, int y){if(x > y)return x;else return y;} 
int main(){ 
    int listenfd, connfd, udpfd, nready, maxfdp1; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    time_t ticks;
    socklen_t len; 
    const int on = 1; 
    struct sockaddr_in cliaddr, servaddr; 
    void sig_chld(int); 
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    listen(listenfd, 10); 
    udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    FD_ZERO(&rset); 
    maxfdp1 = max(listenfd, udpfd) + 1; 
    for (;;) { 
        FD_SET(listenfd, &rset); 
        FD_SET(udpfd, &rset); 
        nready = select(maxfdp1, &rset, NULL, NULL, NULL); 
        char sendBuff[1025];
        if (FD_ISSET(listenfd, &rset)) { 
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                printf("Message From TCP client: "); 
                ticks = time(NULL);
                snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
                write(connfd, sendBuff, strlen(sendBuff)); 
                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
        if (FD_ISSET(udpfd, &rset)) { 
            len = sizeof(cliaddr); 
            bzero(buffer, sizeof(buffer)); 
            printf("\nMessage from UDP client: "); 
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len); 
            puts(buffer); 
            sendto(udpfd, (const char*)message, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
            char ip[100];
            func(buffer , ip);
            printf("Server received DNS name: %s\n", buffer);
            printf("%s resolved to %s" , buffer , ip);
            printf("\n");
        } 
    } 
} 