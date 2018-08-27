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
    server.sin_port=htons(7015);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int b=bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr)); 
    if( b == -1 ) {
        perror("Bind Error\n");
        exit(0);    
    }
    listen(fd, 5);
    int size;
    int newfd=accept(fd, (struct sockaddr*)&client, &size);
    if( newfd == -1 ) {
        perror("Accept Error\n");
        exit(0);    
    }
    
    
    printf("\nWelcome to the server \n\n");
    int query_sal, resp, r, s;
    
    while(1){
    	r = recv(newfd, &query_sal, sizeof(int), 0);
    	if(query_sal <10000){
    		resp = 5;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    	else if(query_sal >= 10000 && query_sal < 30000){
    		resp = 10;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    	else if(query_sal >= 30000 && query_sal < 50000){
    		resp = 20;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    	else if(query_sal >= 50000 && query_sal < 70000){
    		resp = 25;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    	else if(query_sal >= 70000 && query_sal < 100000){
    		resp = 30;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    	else if(query_sal >= 100000){
    		resp = 35;
    		s = send(newfd, &resp, sizeof(int), 0); 
    	}
    }    
    
    close(newfd);
    close(fd);
}
