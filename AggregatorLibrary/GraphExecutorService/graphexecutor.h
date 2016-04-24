#ifndef GRAPHEXECUTOR_H_
#define GRAPHEXECUTOR_H_

#include "graphbuilder.h"

using namespace std;
using namespace GraphBuilderService;

namespace GraphExecutorService {
	class GraphExecutor {
	public:
		virtual void execute(shared_ptr<Graph>) = 0;
		virtual ~GraphExecutor() {}
	};

	class TaskExecutorPool {
	public:
		virtual void submit(shared_ptr<Runnable>) = 0;
		virtual shared_ptr<Runnable> take() = 0;
		virtual ~TaskExecutorPool(){}
	};
	
	template<typename T>
	class ThreadPool {
	private:
		virtual ~ThreadPool() {}
		virtual void worker_thread() {}
	public:
		virtual void submit(T) = 0;
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

	class QueueFactory {
	public:
		static shared_ptr<ThreadSafeQueue<Task>> newSingleLockQueue();
	};
}

#endif /* GRAPHEXECUTOR_H_ */
