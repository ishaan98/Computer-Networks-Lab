
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        /* netbd.h is needed for struct hostent =) */

#define PORT 3550	  /* Open Port on Remote Host */
#define MAXDATASIZE 100   /* Max number of bytes of data */

int main(int argc, char *argv[])
{
  int fd, numbytes;	  /* files descriptors */
  char buf[MAXDATASIZE];  /* buf will store received text */
  
  struct sockaddr_in server;  /* server's address information */

  if (argc !=2) {	      /* this is used because our program will need one argument (IP) */
    printf("Usage: %s <IP Address>\n",argv[0]);
    exit(-1);
  }


  if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  /* calls socket() */
    printf("socket() error\n");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT); /* htons() is needed again */
  server.sin_addr.s_addr =inet_addr(argv[1]); 
  bzero(&(server.sin_zero),8);

  if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){ /* calls connect() */
    printf("connect() error\n");
    exit(-1);
  }

  if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  /* calls recv() */
    printf("recv() error\n");
    exit(-1);
  }

      buf[numbytes]='\0';

      printf("Server Message: %s\n",buf); /* it prints server's welcome message =) */

      close(fd);   /* close fd =) */
	
}
