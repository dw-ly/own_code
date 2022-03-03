#include <iostream>
#include "m_thread_pool.h"
#include "spdlog_common.h"

#include <amqpcpp.h>
#include <amqpcpp/libevent.h>
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
    printf("transfer %d\n", transfers);
    // SPDLOG_INFO_FILE("transfer: {}", transfers);
}

int main()
{
    prctl(PR_SET_NAME, "mthreadm");
    printf("main start\n");
    thread_pool pool;

    int money = 1;
    for (int i = 0; i < 10000; i++)
    {
        Task t = bind(transfer, money);
        pool.add_task(t, i);
    }

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
