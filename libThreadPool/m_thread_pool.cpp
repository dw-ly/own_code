#include "m_thread_pool.h"

void thread_pool::start()
{
    // thread t[max];
    for (int i = 0; i < max; i++)
    {
        // t[i] = thread(&rountine);
    	// printf("add rountine\n");
        threads.emplace_back(thread(&thread_pool::rountine, this, i));
    }
}
void thread_pool::stop()
{
    // unique_lock<std::mutex> lk(m_lock);
    printf("this is stop\n");
    cv.notify_all();
    for (int i = 0; i < max; i++)
    {
        printf("stop thread %d\n", i);
        if (threads[i].joinable())// 等待任务结束， 前提：线程一定会执行完
        {
            printf("join thread %d\n", i);
            threads[i].join();
        }
    }
    
    printf("after join\n");

}
void thread_pool::add_task(Task task, int num)
{
    unique_lock<std::mutex> lk(m_lock);
    // printf("this is add_task:%d\n", num);
    tasks.emplace(task);
    // printf("tasks num:%d\n", tasks.size());
    if (freeNum > 0)
    {
        cv.notify_one();
    }
}
void thread_pool::rountine(int i)
{
    // printf("start new_routine\n");
    string s = "mthread";
    // s += (++i+'0');//char
    s += to_string(i++);//int
    printf("%s\n",s.c_str());
    prctl(PR_SET_NAME, s.c_str());
    int time_out = 0;
    while (1)
    {
        // printf("--------wait for task-------\n");
        unique_lock<std::mutex> lk(m_lock);
        if(tasks.empty())
        {
            time_out ++;
            cv.wait(lk);
            sleep(0);
            if (time_out >= 5)
            {
                return;
            }
            
        }
        else
        {
            time_out = 0;
            if (freeNum > 0)
            {
                auto task = move(tasks.front());
                tasks.pop();
                //printf("start task\n");
                freeNum--;
                task();
                freeNum++;
            }
            else
            {
                sleep(1);
                // cv.wait(lk);
            }
        }
        
    }
    if (freeNum < MAX_THREAD_NUM)
    {
        done = false;
    }
    else
    {
        done = true;
    }
    
}

thread_pool::thread_pool(/* args */)
{
    max = MAX_THREAD_NUM;
    done = true;
    freeNum = MAX_THREAD_NUM;
    printf("max thread num = %d\n", max);
    start();
}

thread_pool::~thread_pool()
{
    if (done)
    {
        // stop();
    }
    // for (auto &t : threads)
    // {
    //     t.join();
    // }
}

