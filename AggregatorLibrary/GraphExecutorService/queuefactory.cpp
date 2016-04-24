#include "graphexecutor.h"
#include "singlelockqueue.cpp"

using namespace GraphExecutorService;

shared_ptr<ThreadSafeQueue<Task>> QueueFactory::newSingleLockQueue() {
	shared_ptr<ThreadSafeQueue<shared_ptr<Task>>> queue(new SingleLockQueue<shared_ptr<Task>>());
	return nullptr;
}
