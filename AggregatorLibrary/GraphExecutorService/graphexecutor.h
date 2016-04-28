#ifndef GRAPHEXECUTOR_H_
#define GRAPHEXECUTOR_H_

#include "graphbuilder.h"
#include <future>

namespace GraphExecutorService {
	using namespace GraphBuilderService;

	class GraphExecutor {
	public:
		virtual void execute(std::shared_ptr<Graph>) = 0;
		virtual ~GraphExecutor() {}
	};

	class TaskPoolExecutor {
	public:
		virtual void submit(std::shared_ptr<Task>) = 0;
		virtual std::shared_ptr<Task> take() = 0;
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
		virtual void submit(std::pair<std::shared_ptr<Task>, std::shared_ptr<ThreadSafeQueue<std::shared_future<std::shared_ptr<Task>>>>>) = 0;
		virtual ~ThreadPool() {}
	};

	class GraphExecutorFactory {
	public:
		static std::shared_ptr<ThreadSafeQueue<std::shared_future<std::shared_ptr<Task>>>> newSingleLockQueue();
		static std::shared_ptr<TaskPoolExecutor> newQueueTaskExecutor();
		static std::shared_ptr<GraphExecutor> newKhansGraphExecutor();
		static std::shared_ptr<ThreadPool> newSingletonThreadPool();
	};
}

#endif /* GRAPHEXECUTOR_H_ */
