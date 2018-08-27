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
    struct sockaddr_in server, client;
    server.sin_family=AF_INET;
    server.sin_port=htons(5040);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int b=bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if( b == -1 ) {
        perror("Bind Error\n");
        exit(0);
    }
    int size;
    listen(fd, 5);
    int newfd=accept(fd, (struct sockaddr*)&client, &size);
    if( newfd == -1 ) {
        perror("Accept Error\n");
        exit(0);
    }
    
    char name[30], res;
    int r=recv(newfd, &name, strlen(name), 0);
    int i, s, len=strlen(name);
    
    for(i=0; i<len; i++)	{
    	res=name[i];
    	if(res=='a' || res=='e' || res=='i' || res=='o' || res=='u'){
    		s=send(newfd, &res, sizeof(char), 0);
    		//printf("%c\t",res);	
    	}
    }
    res='x';
    s=send(newfd, &res, sizeof(char), 0);
    close(newfd);
    close(fd);
}
