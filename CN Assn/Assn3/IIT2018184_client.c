#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

int main(){
	char buffer[100];
	int fd1, t;
	struct sockaddr_in cl_addr;
	fd_set n;
	memset(&cl_addr,0,sizeof(cl_addr));
	fd1 = socket(AF_INET,SOCK_STREAM,0);
	
	cl_addr.sin_family = AF_INET;
	cl_addr.sin_addr.s_addr=INADDR_ANY;
	cl_addr.sin_port=PORT;
	
	t = connect(fd1,(struct sockaddr *)&cl_addr,sizeof(cl_addr));
	
	printf("Enter Message\n");
	while (1){	
		FD_ZERO(&n);
		FD_SET(0,&n);
		FD_SET(fd1,&n);
		int ret=select(10,&n,0,0,0);
		
		if (FD_ISSET(0,&n)){
			fgets(buffer,100,stdin);
			t = send(fd1,buffer,100,0);
				
			if (strncmp(buffer,"bye",3)==0){
				close(fd1);
				return 0;
			}
		}
		if (FD_ISSET(fd1,&n))		{
			t = recv(fd1,buffer,100,0);
			
			if (strncmp(buffer,"bye",3)==0){
				close(fd1);
				return 0;
			}
			printf("\nServer msg: %s\n",buffer);	
		}
	}
	return 0;
}