#ifndef thread_pool_h
#define thread_pool_h

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "task.h"

class ThreadPool {
public:
    void Start();
    void Stop();
    bool AddTask(Task * task);
    void ThreadFunction();
    ThreadPool(int threadNums, int maxTaskNums);
	bool IsFull();
	bool IsEmpty();
    
private:
    std::queue<Task *> mTaskQueue;
    std::condition_variable mCond;
    std::mutex mMutex;
    bool mStop;
    int mMaxQueSize;
    int mThreadNums;
    std::vector<std::thread> mWorkers;
};

#endif  //thread_pool_h
