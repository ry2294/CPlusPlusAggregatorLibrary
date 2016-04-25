#ifndef GRAPHEXECUTOR_H_
#define GRAPHEXECUTOR_H_

#include "graphbuilder.h"
#include <future>

using namespace std;
using namespace GraphBuilderService;

namespace GraphExecutorService {
	class GraphExecutor {
	public:
		virtual void execute(shared_ptr<Graph>) = 0;
		virtual ~GraphExecutor() {}
	};

	class TaskPoolExecutor {
	public:
		virtual void submit(shared_ptr<Task>) = 0;
		virtual shared_ptr<Task> take() = 0;
		virtual ~TaskPoolExecutor(){}
	};
	
	template<typename T>
	class ThreadSafeQueue {
	public:
		virtual void push(T) =0;
		virtual T wait_and_pop() =0;
		virtual bool empty() const =0;
		virtual int size() const=0;
		virtual ~ThreadSafeQueue() {}
	};

	class ThreadPool {
	public:
		virtual void submit(pair<shared_ptr<Task>, shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>>>) = 0;
		virtual ~ThreadPool() {}
	};

	class GraphExecutorFactory {
	public:
		static shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>> newSingleLockQueue();
		static shared_ptr<TaskPoolExecutor> newQueueTaskExecutor();
		static shared_ptr<GraphExecutor> newKhansGraphExecutor();
		static shared_ptr<ThreadPool> newSingletonThreadPool();
	};
}

#endif /* GRAPHEXECUTOR_H_ */
