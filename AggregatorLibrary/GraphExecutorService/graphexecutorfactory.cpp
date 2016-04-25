#include "graphexecutor.h"
#include "singlelockqueue.cpp"
#include "queuetaskexecutor.cpp"
#include "khansgraphexecutor.cpp"
#include "singletonthreadpool.cpp"
#include <future>

using namespace GraphExecutorService;

shared_ptr<GraphExecutor> GraphExecutorFactory::newKhansGraphExecutor() {
	return shared_ptr<GraphExecutor>(new KhansGraphExecutor());
}

shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>> GraphExecutorFactory::newSingleLockQueue() {
	return shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>>(new SingleLockQueue<shared_future<shared_ptr<Task>>>());
}

shared_ptr<TaskPoolExecutor> GraphExecutorFactory::newQueueTaskExecutor() {
	return shared_ptr<TaskPoolExecutor>(new QueueTaskExecutor());
}

shared_ptr<ThreadPool> GraphExecutorFactory::newSingletonThreadPool() {
	static shared_ptr<SingeltonThreadPool> thread_pool{new SingeltonThreadPool()};
	return thread_pool;
}
