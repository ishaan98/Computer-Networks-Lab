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
    server.sin_port=htons(5012);
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
    int a,p,c,d, low, high, i, n, s;
    char res[10];
    n=recv(newfd, &low, sizeof(int), 0);
    n=recv(newfd, &high, sizeof(int), 0);
    for(i=low; i<=high; i++)   {
        c=i;	d=i;	p=0;	a=0;
		
		while(c>0)	{
		a=c % 10;
		p=p + (a*a*a);
		c=c / 10;
		}
		if(p==d) 
			s=send(newfd, &d, sizeof(int), 0);
	}
	if (i==high+1)
        s=send(newfd, &high, sizeof(int), 0);
    close(newfd);
    close(fd);
}
