#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <unistd.h>
#include <thread>
#include <vector>
using namespace std;
#define MAX_THREAD_NUM thread::hardware_concurrency();
using Task = function<void()>;

void print()
{
	printf("this is task\n");
}
class thread_pool
{
private:
    int max;
    bool done;
    queue<Task> tasks;

    vector<thread> threads;
    std::mutex m_lock;
    std::condition_variable cv;
    unique_lock<std::mutex> lk;
public:
    thread_pool(/* args */);
    // thread_pool(thread_pool &&) = default;
    ~thread_pool();
    void start();
    void stop();
    void add_task(Task task);
    void rountine();
};

void thread_pool::start()
{
    // thread t[max];
    for (int i = 0; i < max; i++)
    {
        // t[i] = thread(&rountine);
    	printf("add rountine\n");
        threads.emplace_back(thread(&thread_pool::rountine, this));
    }
}
void thread_pool::stop()
{
    printf("this is stop\n");
    cv.notify_all();
    // for (auto &t : threads)
    // {
    //     t.join();
    // }
    for (int i = 0; i < max; i++)
    {
        threads[i].join();
    }
    
    printf("after join\n");

}
void thread_pool::add_task(Task task)
{
    printf("this is add_task\n");
    tasks.emplace(task);
    cv.notify_one();
}
void thread_pool::rountine()
{
    printf("start new_routine\n");

    while (1)
    {
        while(tasks.empty())
        {
            cv.wait(lk);
        }
        auto task = tasks.front();
        tasks.pop();
		printf("start task\n");
        task();
        this_thread::yield();
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

int main()
{
    thread_pool pool;
	printf("main start\n");
    Task t = bind(print);
    pool.add_task(t);
    pool.add_task(t);
    pool.add_task(t);
  //      printf("threads num %d\n", pool.threads.size());

	printf("main add_task\n");
    usleep(100);
    pool.stop();
	printf("main stop\n");
    usleep(100);

}
