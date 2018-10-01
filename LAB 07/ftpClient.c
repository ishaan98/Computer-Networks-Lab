#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

void error(const char *str)
{
	perror(str);
	exit(1);
}
int main()
{
	int n,sockfd;
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
		error("SOCKET FAILED.");	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(9006);
	server.sin_addr.s_addr=INADDR_ANY;
	n=connect(sockfd,(struct sockaddr*)&server,sizeof(struct sockaddr));
	if(n<0)
		error("CONNECT FAILED");
	FILE *fp;
	fp=fopen("b.txt","w");
	char ch;
	do
	{
		n=recv(sockfd,&ch,sizeof(char),0);
		if(n<0)
			break;
		if(ch!='@')
		{
			printf("%c",ch);
			fprintf(fp,"%c",ch);
		}
	}while(ch!='@');
	fclose(fp);		
	close(sockfd);
	return 0;
}

