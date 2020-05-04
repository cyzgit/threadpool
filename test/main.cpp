#include "thread_pool/thread_pool.h"
#include <chrono>
#include <thread>

#include "test/test_task.h"

int main(){
	TestTask a;
	ThreadPool * pool = new ThreadPool(10,30);
	for(int i = 0; i < 30; ++ i){
		TestTask * curTest = new TestTask;
		pool->AddTask(curTest);
	}
	pool->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pool->Stop();
	return 0;
}
