#include <iostream>
#include <amqpcpp.h>
#include <amqpcpp/libevent.h>

#include "m_thread_pool.h"
#include "spdlog_common.h"
#include "getAverageTimeContrast.h"

#include "net/tcpClient.h"
#include "net/tcpServer.h"
// void print(int time)
// {
// 	printf("this is task,task_time = %d,thread_id = %d\n", time, this_thread::get_id());
//     usleep(time);
// }
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


    Task t1 = bind(tcp_epoll_server_init);
    pool.add_task(t1, 1);
    sleep(2);
    // tcp_epoll_server_init();
    // initTcpClient();
    Task t2 = bind(initTcpClient);
    pool.add_task(t2, 2);
    /* 
        without sleep the main thread, 
        there would be some threads join advance,
        even before the tasks done.
    */
    printf("main add_task\n");
    // pool.stop();
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
