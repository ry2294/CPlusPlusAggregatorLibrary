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

	class ThreadPool {
	public:
		virtual void submit(shared_ptr<Task>) = 0;
		virtual ~ThreadPool() {}
	};
	
	class ThreadSafeQueue {
	public:
		virtual void push(shared_ptr<Task>) =0;
		virtual shared_ptr<Task> wait_and_pop() =0;
		virtual bool empty() =0;
		virtual ~ThreadSafeQueue() {}
	};
}

#endif /* GRAPHEXECUTOR_H_ */
