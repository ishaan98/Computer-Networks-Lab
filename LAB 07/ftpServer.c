

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void error(const char *str)
{
	perror(str);
	exit(1);
}
int main()
{
	int sockfd,n;
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
		error("Socket failed.");
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(9006);
	server.sin_addr.s_addr=INADDR_ANY;
	n=bind(sockfd,(struct sockaddr*)&server,sizeof(struct sockaddr));
	if(n<0)
		error("Binding Failed.");
	listen(sockfd,5);
	int size=sizeof(struct sockaddr);
	int newsockfd=accept(sockfd,(struct sockaddr*)&client,&size);
	if(newsockfd<0)
		error("Accept Failed.");
	system("ls");
	system("ls >s.txt");
	FILE *fp;
	fp=fopen("s.txt","r");
	if(fp==NULL)
		printf("File is empty or doesnt exist");
	char ch;
	while(fscanf(fp,"%c",&ch)!=EOF)
	{
		n=send(newsockfd,&ch,sizeof(ch),0);
		if(n<0)
			error("send");
	}
	ch='@';	
	n=send(newsockfd,&ch,sizeof(ch),0);
	if(n<0)
		error("send");
	fclose(fp);
	close(newsockfd);
	close(sockfd);
	return 0;
}
