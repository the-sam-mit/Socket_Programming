#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT  8181
#define MAXLINE 1024

int main(int argc, char *argv[]) {
  printf("Enter the string\n");
  char ch[100];
  char buffer[MAXLINE];
  scanf("%s", ch);
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in out, serv;
  memset(&out, 0, sizeof(out));
  out.sin_family = AF_INET;
  out.sin_port = htons(PORT);
  out.sin_addr.s_addr = INADDR_ANY;
  sendto(sock, (const char *)ch, strlen(ch), MSG_CONFIRM, (const struct sockaddr *)&out, sizeof(out)); 
  // socklen_t len = sizeof(serv);
  // int n = recvfrom(sock, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &serv, &len);  
  // buffer[n] = '\0'; 
  // printf("Message from server: %s\n", buffer);
  close(sock);
}