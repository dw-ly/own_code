#include "m_thread_pool.h"

void thread_pool::start()
{
    // thread t[max];
    for (int i = 0; i < max; i++)
    {
        // t[i] = thread(&rountine);
    	// printf("add rountine\n");
        threads.emplace_back(thread(&thread_pool::rountine, this));
    }
}
void thread_pool::stop()
{
    unique_lock<std::mutex> lk(m_lock);
    // printf("this is stop\n");
    cv.notify_all();
    for (int i = 0; i < max; i++)
    {
        threads[i].join();
    }
    
    // printf("after join\n");

}
void thread_pool::add_task(Task task)
{
    unique_lock<std::mutex> lk(m_lock);
    printf("this is add_task\n");
    tasks.emplace(task);
    cv.notify_one();
}
void thread_pool::rountine()
{
    // printf("start new_routine\n");
    
    while (1)
    {
        // printf("--------wait for task-------\n");
        unique_lock<std::mutex> lk(m_lock);
        if(tasks.empty())
        {
            cv.wait(lk);
        }
        else
        {
            auto task = tasks.front();
            tasks.pop();
		    printf("start task\n");
            task();
        }
        
    }
}

thread_pool::thread_pool(/* args */)
{
    max = MAX_THREAD_NUM;
    done = false;
    printf("max thread num = %d\n", max);
    start();
}

thread_pool::~thread_pool()
{
    if (done)
    {
        stop();
    }
    // for (auto &t : threads)
    // {
    //     t.join();
    // }
}

