#pragma once
#include <iostream>
#include <chrono> 
#include <functional>
using namespace std;
using Task = function<void()>;
chrono::duration<double> getOneTime(Task t)
{
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now(); 
	//需测试运行时间的代码1
    t();
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    return time_used;
}
double getAverageTimeByN(Task t, int N)
{
    double time_all = 0;
    for (int i = 0; i < N; i++)
    {
        time_all += getOneTime(t).count();
    }
    return time_all/N;
    
}
// void mexample1()
// {

// }
// void mexample2()
// {

// }
int do_test(function<void()> f1, function<void()> f2)
{
    // Task t1 = bind(example1);
    // Task t2 = bind(example2);

    Task t1 = bind(f1);
    Task t2 = bind(f2);

    int n = 1000;//average time
	
    cout << "run average time1 = " << getAverageTimeByN(t1, n) << " seconds. " << endl;
    
    cout << "run average time2 = " << getAverageTimeByN(t2, n) << " seconds. " << endl;
	return 0;
}