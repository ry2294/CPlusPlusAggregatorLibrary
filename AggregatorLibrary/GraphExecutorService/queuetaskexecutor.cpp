#include "graphexecutor.h"
#include <future>

using namespace std;
using namespace GraphExecutorService;

class QueueTaskExecutor : public TaskPoolExecutor {
private:
	shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>> tasksQueue;
	shared_ptr<ThreadPool> threadPool;
public:
	QueueTaskExecutor() : tasksQueue{GraphExecutorFactory::newSingleLockQueue()},
		threadPool{GraphExecutorFactory::newSingletonThreadPool()}{
	}

	void submit(shared_ptr<Task> task) {
		threadPool->submit(pair<shared_ptr<Task>, shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>>>(task, tasksQueue));
	}

	shared_ptr<Task> take() {
		shared_future<shared_ptr<Task>> future = tasksQueue->wait_and_pop();
		return future.get();
	}

	~QueueTaskExecutor(){
	}
};
