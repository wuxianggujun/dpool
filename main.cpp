#include <iostream>
#include "ThreadPool.hpp"
#include <chrono>
#include <mutex>

using namespace dpool;

std::mutex coutMtx;

void task(int taskid){
    {
        std::lock_guard<std::mutex> guard(coutMtx);
        std::cout << "Task " << taskid << " is running" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> guard(coutMtx);
        std::cout << "Task " << taskid << " is done" << std::endl;
    }
}


void monitor(const ThreadPool &pool, int seconds)
{
    for (int i = 1; i < seconds * 10; ++i)
    {
        {
            std::lock_guard<std::mutex> guard(coutMtx);
            std::cout << "thread num: " << pool.threadsNum() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {

    ThreadPool pool(100);

    pool.submit(monitor,std::ref(pool), 13);

    for (int taskId = 0; taskId < 100; ++taskId) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        pool.submit(task, taskId); // 提交任务
    }
    return 0;
}
