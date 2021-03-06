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
    server.sin_port=htons(5040);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if( c == -1 ) {
        perror("Connect Error\n");
        exit(0);
    }
    
    char name[30], res;
    printf("Enter the name : ");
    gets(name);
    int s=send(fd, &name, strlen(name), 0);
    int r;
    printf("\nThe vowels in the name are :\n");
    while(res != 'x'){
    	r=recv(fd, &res, sizeof(char), 0);
    	if(res != 'x')
    		printf(" %c\t", res);
    }
    close(fd);
}
