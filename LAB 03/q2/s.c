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
	server.sin_port = htons(7217);
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
  if(fd==-1){
  	perror("Accept error\n");
  	exit(0);
  }
  else
  	printf("Accept successfull\n");

  int a[5];
  int j;
	int r = recv(newfd, &a, sizeof(a), 0);

  int min = a[0];
  int max = a[0];

  /*
  for(int i=0; i<5; i++){
    printf("%d\t",a[i]);
  }
  */

  for(int i=1; i<5; i++){
    if(a[i] < min)
      min = a[i];
    if(a[i] > max)
      max = a[i];
  }

  send(newfd, &min, sizeof(int), 0);
  send(newfd, &max, sizeof(int), 0);

  close(newfd);
	close(fd);

}
