#include "graphexecutor.h"
#include "singlelockqueue.cpp"
#include "queuetaskexecutor.cpp"
#include "khansgraphexecutor.cpp"

using namespace GraphExecutorService;

shared_ptr<GraphExecutor> GraphExecutorFactory::newKhansGraphExecutor() {
	return shared_ptr<GraphExecutor>(new KhansGraphExecutor());
}

shared_ptr<ThreadSafeQueue<Task>> GraphExecutorFactory::newSingleLockQueue() {
	shared_ptr<ThreadSafeQueue<shared_ptr<Task>>> queue(new SingleLockQueue<shared_ptr<Task>>());
	return nullptr;
}

shared_ptr<TaskPoolExecutor> GraphExecutorFactory::newQueueTaskExecutor() {
	return shared_ptr<TaskPoolExecutor>(new QueueTaskExecutor());
}
