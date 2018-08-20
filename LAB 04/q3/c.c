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
    server.sin_port=htons(5012);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if( c == -1 ) {
        perror("Connect Error\n");
        exit(0);    
    }
    int low, high, x, r, i;
    char str[10];
    strcpy(str, " ");
    printf("Enter the lower limit : ");
    scanf("%d", &low);
    int s=send(fd, &low, sizeof(int), 0);
    printf("Enter the upper limit : ");
    x=low;
    scanf("%d", &high);
    s=send(fd, &high, sizeof(int), 0);
    printf("The armstrong numbers are : \n");
    while(1)	{
        r=recv(fd, &x, sizeof(int), 0);
        if((x+1)==(high+1))
        	break;
        printf("%d\n", x);
    }
    close(fd);
}
