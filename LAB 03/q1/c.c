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
	server.sin_port = htons(7216);
	server.sin_addr.s_addr = inet_addr("192.168.122.1");
	if((connecter = connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){
		perror("Connection error\n");
		exit(0);
	}
	else
		printf("Connection successful\n");



  int a[2];
  printf("Enter 2 nos:\n");
  for(int i=0; i<2; i++){
    scanf("%d",&a[i]);
  }
  send(fd, &a, sizeof(a), 0);

  int gcd;
  int r = recv(fd, &gcd, sizeof(int), 0);

  printf("The gcd: %d\n", gcd);

	close(fd);

}
