#include<stdio.h>
#include <sys/socket.h>

int fd;

int main(){
	if((fd=socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP))==-1)
		printf("Error");
	else
		printf("Established \nsocket: %d\n",fd);
}


