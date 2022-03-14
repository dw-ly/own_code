// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <errno.h>
// #include <pthread.h>
// #include <ctype.h>
// #include <arpa/inet.h>

#include "netHeader.h"
#define 	SERV_PORT 6666   

using namespace std;
int initTcpClient()
{
	printf("start init client");
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("socket failed!\n");
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SIN_PORT1);//SERV_PORT
	serv_addr.sin_addr.s_addr = inet_addr("10.0.12.17");  //任意的IP地址htonl(INADDR_ANY)
	
	int ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret == -1){
		printf("connect error!\n");
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



