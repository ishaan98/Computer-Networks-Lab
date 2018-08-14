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
	server.sin_port = htons(7217);
	server.sin_addr.s_addr = inet_addr("192.168.122.1");
	if((connecter = connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){
		perror("Connection error\n");
		exit(0);
	}
	else
		printf("Connection successful\n");

    char res[10];

  printf("Enter length: \n");
  int len;
  scanf("%d",&len);
  int s1 = send(fd, &len, sizeof(int), 0);
  int a[len],s,r;

  printf("Enter %d nos:\n",len);
  for(int i=0; i<len; i++){
    scanf("%d",&a[i]);
    s  = send(fd, &a[i], sizeof(int), 0);
    r = recv(fd, &res, sizeof(res), 0);
    printf("%d is %s\n",a[i], res);
  }

	close(fd);

}
