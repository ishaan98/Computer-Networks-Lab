#include<stdio.h>
#include <sys/socket.h>

int fd;

int main(){
	if((fd=socket(AF_LOCAL, SOCK_STREAM, 0))==-1)
		printf("Error");
	else
		printf("Established \nsocket: %d\n",fd);
}


