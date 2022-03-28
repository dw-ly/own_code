#include <iostream>
// #include <amqpcpp.h>
// #include <amqpcpp/libevent.h>

#include "m_thread_pool.h"
// #include "spdlog_common.h"
#include "getAverageTimeContrast.h"

// #include "net/tcpClient.h"
// #include "net/tcpServer.h"
// void print(int time)
// {
// 	printf("this is task,task_time = %d,thread_id = %d\n", time, this_thread::get_id());
//     usleep(time);
// }
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
// #include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>

// #include "netHeader.h"
#define 	SERV_PORT 6666   

using namespace std;
int initTcpClient2()
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
    string s = "testclient11111111\n";
    for (int i = 0; i < 10; i++)
    {
        // send(sockfd, s.c_str(), sizeof(s), 0);
        //"connect success---\n"
    }
	write(sockfd,s.c_str(),20);
    
	// write(sockfd,"connect success\n",20);
	
	while(sockfd != -1){
		sleep(1);
	}  //等待
	
	close(sockfd);
	printf("111111111");
	return sockfd;
}

mutex fun_lock;
int transfers = 0;
void transfer(int &time)
{
    lock_guard<mutex> guard(fun_lock);
    transfers += time;
    if (transfers == 10000)
    {
        printf("transfers %d\n",transfers);
    }
    
    // printf("transfer %d\n", transfers);
    // SPDLOG_INFO_FILE("transfer: {}", transfers);
}
void test_string_append()
{
    string s1 = "mthread";
    string s2 = "mthread";
    do_test(
        [&s1]()
        {
            for (int i = 0; i < 1; i++)
            {
                s1 += "s";
            }
            
            
        }, 
        [&s2]()
        {
            for (size_t i = 0; i < 1; i++)
            {
                s2 = s2 + "s";
            }
        });
}
int main()
{
    prctl(PR_SET_NAME, "mthreadm");
    printf("main start\n");
    thread_pool pool;

    // int money = 1;
    // for (int i = 0; i < 10000; i++)
    // {
    //     Task t = bind(transfer, money);
    //     pool.add_task(t, i);
    // }
    // sleep(10);


    // Task t1 = bind(tcp_epoll_server_init);
    // pool.add_task(t1, 1);
    // sleep(2);
    // tcp_epoll_server_init();
    // initTcpClient();
    Task t2 = bind(initTcpClient2);
    Task t3 = bind(initTcpClient2);
    Task t4 = bind(initTcpClient2);
    Task t5 = bind(initTcpClient2);
    pool.add_task(t2, 1);
    pool.add_task(t3, 2);    
    pool.add_task(t4, 3);
    pool.add_task(t5, 4);
    pool.add_task(t2, 5);
    pool.add_task(t3, 6);
    pool.add_task(t4, 7);
    pool.add_task(t5, 8);
    /* 
        without sleep the main thread, 
        there would be some threads join advance,
        even before the tasks done.
    */
    printf("main add_task\n");
    pool.stop();
    printf("main stop\n");

}
// int main()
// {
//     thread_pool pool;
//     printf("main start\n");
//     srand((int)time(0));
//     for (int i = 0; i < 3; i++)
//     {
//         int time = rand()%100;
//         Task t = bind(print, time);
//         pool.add_task(t);
//     }

//     printf("main add_task\n");
//     usleep(100);
//     pool.stop();
//     printf("main stop\n");
//     usleep(100);

// }
