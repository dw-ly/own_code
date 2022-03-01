#include <iostream>
#include "m_thread_pool.h"
#include "spdlog_common.h"

// void print(int time)
// {
// 	printf("this is task,task_time = %d,thread_id = %d\n", time, this_thread::get_id());
//     usleep(time);
// }

void transfer(int time)
{
    time++;
    SPDLOG_INFO_FILE("transfer %d", time);
}
int main()
{
    thread_pool pool;
    int money = 0;
    printf("main start\n");
    for (int i = 0; i < 3; i++)
    {
        Task t = bind(transfer, money);
        pool.add_task(t);
    }

    printf("main add_task\n");
    usleep(100);
    pool.stop();
    printf("main stop\n");
    usleep(100);

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
