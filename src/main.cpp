#include <iostream>
#include "thread_pool.h"

void print(int time)
{
	printf("this is task,task_time = %d,thread_id = %d\n", time, this_thread::get_id());
    usleep(time);
}

int main()
{
    thread_pool pool;
    printf("main start\n");
    srand((int)time(0));
    for (int i = 0; i < 3; i++)
    {
        int time = rand()%100;
        Task t = bind(print, time);
        pool.add_task(t);
    }

    printf("main add_task\n");
    usleep(100);
    pool.stop();
        printf("main stop\n");
    usleep(100);

}
