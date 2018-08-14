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

struct Employee{
  char name[20];
  int basic;
  int da;
  int ta;
}emp;

int main(){

	if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1){
		perror("Socket error\n");
		exit(0);
	}
	else
		printf("Socket creation successful\n");
	server.sin_family = AF_INET;
	server.sin_port = htons(7218);
	server.sin_addr.s_addr = inet_addr("192.168.122.1");
	if((connecter = connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){
		perror("Connection error\n");
		exit(0);
	}
	else
		printf("Connection successful\n");

    char res[10];

  printf("Enter name of employee: \n");
  gets(emp.name);
  printf("Enter the basic salary: \n");
  scanf(" %d", &emp.basic);
  printf("Enter da of employee: \n");
  scanf(" %d", &emp.da);
  printf("Enter ta of employee: \n");
  scanf(" %d", &emp.ta);

  int s = send(fd, (struct employee *)&emp, sizeof(struct Employee), 0);

  int total;

  int r = recv(fd, &total, sizeof(int), 0);

  printf("Total salary: %d\n", total);

	close(fd);

}
