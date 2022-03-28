#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>

// #include "netHeader.h"
#define 	SERV_PORT 6666   

using namespace std;
int initTcpClient()
{
	printf("start init client\n");
	int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd == -1){
		printf("socket failed!\n");
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);//SERV_PORT  10.0.12.17
	serv_addr.sin_addr.s_addr = inet_addr("47.106.133.127");  //任意的IP地址htonl(INADDR_ANY)
	printf("start connect\n");
	
	int ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret == -1){
		printf("connect error! errno=%d\n", errno);
		return -2;
	}
	
	//connect success
	write(sockfd,"connect success\n",20);
	
	while(sockfd != -1){
		sleep(1);
	}  //等待
	
	close(sockfd);
	printf("111111111");
	return sockfd;
}

int main()
{
	initTcpClient();
}



