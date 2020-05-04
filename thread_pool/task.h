#ifndef task_h
#define task_h

#include "noncopyable.h"

enum TaskStatus {
	StatusWait = 0,
	StatusRunning = 1,
	StatusOver = 2
};

class Task : NonCopyAble {
public:
    virtual void Run() = 0;
	void SetStatus(TaskStatus st){
		mStatus = st;
	}
	TaskStatus GetStatus(){
		return mStatus;
	}
private:
    TaskStatus mStatus;
};


#endif /* task_h */
