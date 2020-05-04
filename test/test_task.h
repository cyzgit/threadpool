#include <iostream>
#include <chrono>
#include <thread>

#include "thread_pool/task.h"
class TestTask : public Task {

public:	
	virtual void Run(){
		std::cout<<"one test task run!"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	};
};
