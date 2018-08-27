#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

struct details{
	char name[20];
	int roll;
	char addr[100];
}response;

int main()  {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( fd == -1 ) {
        perror("Socket Error\n");
        exit(0);    
    }
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(7012);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if( c == -1 ) {
        perror("Connect Error\n");
        exit(0);    
    }
    
    int roll, s, r;
    int ch=1;
   	while(ch){
   		printf("Enter roll no: \n");
   		scanf("%d",&roll);
   		s = send(fd, &roll, sizeof(int), 0);
   		printf("\nSearching\n\n");
   		r = recv(fd, &response, sizeof(response), 0);
   		printf("Name: %s\n", response.name);
   		printf("Roll: %d\n", response.roll);
   		printf("Address: %s\n",  response.addr);
   		printf("\nSearch another student details? (Y=1|N=0)\n");
   		scanf("%d", &ch);   		
   	}
   	
    
    close(fd);
}
