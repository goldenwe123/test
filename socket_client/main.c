#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 500000 
#define PORT 5134 
#define SA struct sockaddr 


char buff[MAX]; 

void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("172.16.114.52"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
	
	struct  timeval start;
	struct  timeval end;
	unsigned  long diff;

	float count = 0;
	gettimeofday(&start,NULL);
	for (;;) { 
		
		
		float len = read(sockfd, buff, sizeof(buff));
		count += len;
		gettimeofday(&end,NULL);
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		diff = diff/1000;
		//printf("count:%d\n",len);
		if( diff > 1000) {
			
			float speed = count / 1024 / diff * 1000 * 8;
			printf("count : %f Speed %f Mb\n",count,speed);
			count = 0;
			
			
			gettimeofday(&start,NULL);
			
		}
		
		
		//printf("len:%d\n",len);
		//printf("thedifference is %ld\n",diff);
		

	}
  
    // function for chat 
    //func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 