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

int findMin(int a[2]){
  if(a[0] > a[1])
    return 1;
  else if(a[0] < a[1])
    return 0;
  else
    return -1;
}

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
	server.sin_port = htons(7216);
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

  int a[2];
  int j;
	int r = recv(newfd, &a, sizeof(a), 0);
	int i = findMin(a);
  printf("The func returned %d\n",i);
  int gcd;

  if(i==-1){
    gcd = a[1];
  }
  else{
    for(j=a[i]; j>=1; j--){
        if(j%a[0]==0 && j%a[1]==0){
          gcd = j;
          break;
        }
    }
  }
  printf("gcd = %d\n",gcd);
  printf("Calculation complete\n");
  send(newfd, &gcd, sizeof(int), 0);

  close(newfd);
	close(fd);

}
