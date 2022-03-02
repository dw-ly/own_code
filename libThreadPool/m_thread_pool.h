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
using namespace std;
#define MAX_THREAD_NUM thread::hardware_concurrency();
using Task = function<void()>;
class thread_pool
{
public:
    int max;
    bool done;
    queue<Task> tasks;
    vector<thread> threads;
    std::mutex m_lock;
    std::condition_variable cv;
public:
    thread_pool();
    ~thread_pool();
    void start();
    void stop();
    void add_task(Task task);
    void rountine(int i);
};


