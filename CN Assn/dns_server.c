#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>

#include <arpa/inet.h>
#define PORT     8181
#define MAXLINE  1024 

int func(char * hostname , char* ip){
  struct hostent *he;
  struct in_addr **addr_list;
  int i;
  if ( (he = gethostbyname(hostname) ) == NULL){
    herror("gethostbyname");
    return 1;
  }
  addr_list = (struct in_addr **) he->h_addr_list;
  for(i = 0; addr_list[i] != NULL; i++){
    strcpy(ip , inet_ntoa(*addr_list[i]));
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
    char buffer[MAXLINE];
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in s_address, cliaddr;
    memset(&s_address, 0, sizeof(s_address));
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(PORT);
    s_address.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (const struct sockaddr *)&s_address, sizeof(s_address));
    socklen_t len = sizeof(cliaddr);
    int n = recvfrom(sock, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    buffer[n] = '\0'; 
    char ip[100];
    func(buffer , ip);
    printf("Server received DNS name: %s\n", buffer);
    printf("%s resolved to %s" , buffer , ip);
    printf("\n");
    close(sock);
}