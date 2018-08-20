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
	server.sin_port = htons(7211);
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

  int size;
  int newfd = accept(fd, (struct sockaddr *)&client, &size);
  if(newfd==-1){
  	perror("Accept error\n");
  	exit(0);
  }
  else
  	printf("Accept successfull\n");

  int n,len,s,r;

  char resp_msg[200];
  char inc_msg[200];

  while(1){
    r = recv(newfd, &inc_msg, sizeof(inc_msg), 0);
    if(!strcmp(inc_msg,"bye")){
        printf("Ending conversation\n");
        break;
    }
    printf("Client: %s\n",inc_msg);
    printf("Server: ");
    gets(resp_msg);
    printf("\n");
    s = send(newfd, &resp_msg, sizeof(resp_msg), 0);
    if(!strcmp(resp_msg,"bye")){
      printf("Ending conversation\n");
      break;
    }
  }

  printf("\n");
  close(newfd);
	close(fd);

}





















//printf("Accept connection from %s", inet_ntoa(client.sin_addr));
