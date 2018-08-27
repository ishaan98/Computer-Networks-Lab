#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main()  {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( fd == -1 ) {
        perror("Socket Error\n");
        exit(0);    
    }
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(7015);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if( c == -1 ) {
        perror("Connect Error\n");
        exit(0);    
    }
    
    int sal, s, r, resp;
    int ch=1;
   	while(ch){
   		printf("Enter Salary: \n");
   		scanf("%d",&sal);
   		s = send(fd, &sal, sizeof(int), 0);
   		printf("\nSearching\n\n");
   		r = recv(fd, &resp, sizeof(int), 0);
   		printf("Increment: %d percent \n",  resp);
   		printf("\nSearch again? (Y=1|N=0)\n");
   		scanf("%d", &ch);   		
   	}
   	
    
    close(fd);
}
