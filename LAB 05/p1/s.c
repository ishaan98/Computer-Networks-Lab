#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

typedef struct details{
	char name[20];
	int roll;
	char addr[100];
}Student;

Student student_array[5];

int main()  {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( fd == -1 ) {
        perror("Socket Error\n");
        exit(0);    
    }
    struct sockaddr_in server, client;
    server.sin_family=AF_INET;
    server.sin_port=htons(7012);
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
    
    // building the database
    strcpy(student_array[0].name,"Ishaan");
    strcpy(student_array[0].addr,"Mumbai, India");
    student_array[0].roll = 1605612;
    
    student_array[1].roll = 1605583;
    strcpy(student_array[1].name,"Saurav");
    strcpy(student_array[1].addr,"Gaur, Nepal");
    
    
    student_array[2].roll = 1605595;
    strcpy(student_array[2].name,"Amit");
    strcpy(student_array[2].addr,"Bhubaneshwar, India");
    
    student_array[3].roll = 1605570;
    strcpy(student_array[3].name,"Pankaj");
    strcpy(student_array[3].addr,"Kathmandu, Nepal");
    
    student_array[4].roll = 1605581;
    strcpy(student_array[4].name,"Rahul");
    strcpy(student_array[4].addr,"Chennai, India");
    
    int query_roll, r, s;
    
    printf("\nWelcome to the server \n\n");
    
    while(1){
    	r = recv(newfd, &query_roll, sizeof(int), 0);
    	for(int i=0; i<5; i++){
    		if(query_roll == student_array[i].roll){
    			s = send(newfd, (Student *)&student_array[i], sizeof((Student)student_array[i]), 0);
    			break;
    		};
    	}
    }    
    
    close(newfd);
    close(fd);
}
