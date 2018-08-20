#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int fd;
struct sockaddr_in server, client;

int main(){

	// socket creation
	fd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd==-1){
		perror("Socket error\n");
		exit(0);
	}
	else
		printf("Socket created, Details: %d\n", fd);

	// setting the data to server structure
	server.sin_family = AF_INET;
	server.sin_port = htons(7215);
	server.sin_addr.s_addr = inet_addr("192.168.122.1");

	// creating a binder
	int binder = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
	if(binder==-1){
		perror("Bind error\n");
		exit(0);
	}
	else
		printf("Successful binding\n");

	// 5 signifies the number of connections. Acts as a limiter that limits the number of connections
	listen(fd, 5);

  int newfd;

  int r;
  char ip_addr[100];

  while(1){
    int size;
    newfd = accept(fd, (struct sockaddr *)&client, &size);
    if(newfd==-1){
    	perror("Accept error\n");
    	exit(0);
    }
    else{
      printf("Accept successfull\n");
      r = recv(newfd, &ip_addr, sizeof(ip_addr), 0);
      printf("IP : %s\n",ip_addr);
    }
  }

  printf("\n");
  close(newfd);
	close(fd);

}
