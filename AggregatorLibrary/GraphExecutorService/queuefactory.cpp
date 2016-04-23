#include "graphexecutor.h"
#include "singlelockqueue.cpp"

using namespace GraphExecutorService;

shared_ptr<ThreadSafeQueue<Task>> QueueFactory::newSingleLockQueue() {
	//shared_ptr<ThreadSafeQueue<Task>> queue(new SingleLockQueue<Task>());
	return nullptr;
}
