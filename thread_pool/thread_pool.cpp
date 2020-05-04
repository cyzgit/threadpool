#include <iostream>

#include "thread_pool.h"

ThreadPool::ThreadPool(int threadNums, int maxTaskNums){
    mThreadNums = threadNums;
    mMaxQueSize = maxTaskNums;
	mStop = false;
}

void ThreadPool::Start(){
    for(int i = 0; i < mThreadNums; ++ i){
        mWorkers.emplace_back(std::bind(&ThreadPool::ThreadFunction, this));
    }
}

void ThreadPool::Stop(){
	mStop = true;
 	for(auto & ct : mWorkers){
		ct.join();
	}   
}

bool ThreadPool::AddTask(Task * task){
	std::unique_lock<std::mutex> lk(mMutex);
	if(mTaskQueue.size() >= mMaxQueSize){
		return false;
	}
	mTaskQueue.push(task);
    mCond.notify_all();
    return true;
}

bool ThreadPool::IsFull(){
	std::unique_lock<std::mutex> lk(mMutex);
	return mTaskQueue.size() >= mMaxQueSize;
}

bool ThreadPool::IsEmpty(){
	std::unique_lock<std::mutex> lk(mMutex);
	return mTaskQueue.empty();
}

void ThreadPool::ThreadFunction(){
    while(!mStop){
        Task * curTask = nullptr;
        {
            std::unique_lock<std::mutex> ulock(mMutex);
            while(mTaskQueue.empty()){
                mCond.wait(ulock, [this] {return !this->mTaskQueue.empty();});
            }
            curTask = mTaskQueue.front();
            mTaskQueue.pop();
        }
		if(curTask == nullptr){
			continue;
		}
		curTask->SetStatus(StatusRunning);
        curTask->Run();
		curTask->SetStatus(StatusOver);
    }
}



