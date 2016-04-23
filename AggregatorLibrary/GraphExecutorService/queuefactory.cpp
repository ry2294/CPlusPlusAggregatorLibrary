#include "graphexecutor.h"
#include "singlelockqueue.cpp"

using namespace GraphExecutorService;

shared_ptr<ThreadSafeQueue> QueueFactory::newSingleLockQueue() {
	shared_ptr<ThreadSafeQueue> queue(new SingleLockQueue());
	return queue;
}
