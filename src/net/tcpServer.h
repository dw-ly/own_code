//tcp server epoll并发服务器 
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <errno.h>
// #include <pthread.h>
// #include <ctype.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>

// #include <sys/epoll.h>

#include "netHeader.h"
#define  MAX_LINK_NUM   128
#define  SERV_PORT      6666
#define  BUFF_LENGTH    320
#define  MAX_EVENTS     5

int  count = 0;

int tcp_epoll_server_init(){
	
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("socket error!\n");
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in clit_addr;
	socklen_t clit_len;
	
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SIN_PORT1);//SERV_PORT
	serv_addr.sin_addr.s_addr = inet_addr("10.0.12.17");//htonl(SIN_ADDR1);// 任意本地ip INADDR_ANY
	// inet_pton(AF_INET, SIN_ADDR1, &serv_addr.sin_addr.s_addr);
	int ret = bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret == -1){
		printf("bind error! ret=%d, errno=%d\n", ret, errno);
		return -2;
	}
	
	listen(sockfd,MAX_LINK_NUM);
	
	
	//创建epoll
	int  epoll_fd = epoll_create(MAX_EVENTS);
	if(epoll_fd == -1){
		printf("epoll_create error!\n");
		return -3;
	}
	
	//向epoll注册sockfd监听事件
	struct epoll_event ev;   //epoll事件结构体
	struct epoll_event events[MAX_EVENTS];  //事件监听队列
	
	ev.events = EPOLLIN;
	ev.data.fd = sockfd;
	
	int ret2 = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&ev);
	if(ret2 == -1){
		printf("epoll_ctl error!\n");
		return -4;
	}
	int connfd = 0;
	while(1){
		printf("epoll_wait\n");
		//epoll等待事件
			int nfds = epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
			if(nfds == -1){
				printf("epoll_wait error!\n");
				return -5;
			}
			printf("nfds: %d\n",nfds);
			//检测
			for(int i = 0;i<nfds;++i){
				printf("client: %d\n",i);

				//客服端有新的请求
				if(events[i].data.fd == sockfd){
					 connfd =  accept(sockfd,(struct sockaddr*)&clit_addr,&clit_len);
					if(connfd == -1){
						printf("accept error!\n");
						return -6;
					}
					
					ev.events = EPOLLIN;
					ev.data.fd = connfd;
					if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connfd,&ev) == -1){
						printf("epoll_ctl add error!\n");
						return -7;
					}
					
					printf("accept client: %s\n",inet_ntoa(clit_addr.sin_addr));
					// printf("client %d\n",++count);
				}
				//客户端有数据发送过来
				else{
					char buff[BUFF_LENGTH];
					int ret1 = read(connfd,buff,sizeof(buff));
					printf("%s",buff);
				}
			}
		
	}
	
	close(connfd);
	return 0;
	
}

// int main(){
// 	tcp_epoll_server_init();
// }
