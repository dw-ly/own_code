#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <unistd.h>
#include <thread>
#include <vector>
#include <ctime>
#include <sys/prctl.h>
#include <atomic>
using namespace std;
#define MAX_THREAD_NUM 8//thread::hardware_concurrency();
using Task = function<void()>;
class thread_pool
{
public:
    int max;
    bool done;
    atomic_int freeNum;
    queue<Task> tasks;
    vector<thread> threads;
    std::mutex m_lock;
    std::condition_variable cv;
public:
    thread_pool();
    ~thread_pool();
    void start();
    void stop();
    void add_task(Task task, int num/*test*/);
    void rountine(int i);
};


