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
	int fd1, fd2, t;
	socklen_t len;
	char buf[100];
	fd_set n;
	struct sockaddr_in s_address, c_address;
	memset(&s_address,0,sizeof(s_address));
	memset(&c_address,0,sizeof(c_address));
	fd1 = socket(AF_INET,SOCK_STREAM,0);
	s_address.sin_family=AF_INET;
	s_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	s_address.sin_port=PORT;
	t = bind(fd1,(struct sockaddr *)&s_address,sizeof(s_address));
	t = listen(fd1,20);
	len = sizeof(c_address);
	fd2 = accept(fd1,(struct sockaddr *)&c_address, &len);
	printf("Enter Message\n");
	while (1){
		FD_ZERO(&n);
		FD_SET(0,&n);
		FD_SET(fd2,&n);
		int ret=select(10,&n,0,0,0);
		
		if (FD_ISSET(0,&n)){
			fgets(buf,100,stdin);
			
			t = send(fd2,buf,100,0);
			
			if (strncmp(buf,"bye",3)==0){
				close(fd2);
				close(fd1);
				return 0;
			}
		}
		if (FD_ISSET(fd2,&n)){
			t = recv(fd2,buf,100,0);
			if (strncmp(buf,"bye",3)==0){
				close(fd2);
				close(fd1);
				return 0;
			}
			printf("\nClient msg: %s\n",buf);	
		}
	}
	close(fd2);
	close(fd1);
	return 0;
}