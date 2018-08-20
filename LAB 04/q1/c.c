#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>        /* netbd.h is needed for struct hostent =) */
#include<unistd.h>

int fd;
struct sockaddr_in server;
int connecter;

int main(){

	if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1){
		perror("Socket error\n");
		exit(0);
	}
	else
		printf("Socket creation successful\n");
	server.sin_family = AF_INET;
	server.sin_port = htons(7211);
	server.sin_addr.s_addr = inet_addr("192.168.122.1");
	if((connecter = connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){
		perror("Connection error\n");
		exit(0);
	}
	else
		printf("Connection successful\n");

  printf("Start Chatting\n");

  char quer_msg[200];
  char resp_msg[200];

  int r,s;

  while(1){
    printf("Client: ");
    gets(quer_msg);
    s = send(fd, &quer_msg, sizeof(quer_msg), 0);
    if(!strcmp(quer_msg,"bye")){
        printf("Ending conversation\n");
        break;
    }
    r = recv(fd, &resp_msg, sizeof(resp_msg), 0);
    if(!strcmp(resp_msg,"bye")){
        printf("Ending conversation\n");
        break;
    }
    printf("Server: %s\n", resp_msg);
  }

	close(fd);

}
