#ifndef GRAPHEXECUTOR_H_
#define GRAPHEXECUTOR_H_

#include "graphbuilder.h"
#include <future>

namespace GraphExecutorService {
	using namespace GraphBuilderService;

	/*
	 * Interface for Graph Executor which executes the Graph level by level.
	 */
	class GraphExecutor {
	public:
		/**
		 * The execute function communicates with the TaskPoolExecutor to execute the graph.
		 * It takes a shared_ptr of a GraphBuilder and executes the graph.
		 */
		virtual void execute(std::shared_ptr<GraphBuilder>) = 0;
		virtual ~GraphExecutor() {}
	};

	/*
	 *Interface for TaskPoolExecutor which is used by Graph Executor to communicate with ThreadPool.
	 */
	class TaskPoolExecutor {
	public:
		virtual void submit(std::shared_ptr<Task>) = 0;
		virtual std::shared_ptr<Task> take() = 0;
		virtual ~TaskPoolExecutor(){}
	};
	
	/**
	 * Interface for a ThreadSafeQueue which is used by the ThreadPool and used for implementing task queue.
	 */ 
	template<typename T>
	class ThreadSafeQueue {
	public:
		/**
		 * The push function allows the program to add an element on to the threadsafequeue.
		 */
		virtual void push(T) =0;
		
		/**
		 * The wait_and_pop function pops the top element and returns it. In case the queue is empty and a 
		 * thread is requesting for wait and pop, then the thread must be asked to wait and notified as soon as 
		 * an element is added into the queue.
		 */
		virtual T wait_and_pop() =0;
		
		/**
		 * The empty function checks if the queue is empty or not.
		 */
		virtual bool empty() const =0;
		
		/**
		 * The size function returns the number of elements in the queue.
		 */
		virtual int size() const=0;
		virtual ~ThreadSafeQueue() {}
	};

	/*
	 * Interface for ThreadPool which maintains worker threads for executing tasks submitted by TaskPoolExecutors.
	 */
	typedef  std::shared_ptr<ThreadSafeQueue<std::shared_future<std::shared_ptr<Task>>>> return_queue; 
	class ThreadPool {
	public:
		/**
		 * The submit functions takes a pair of shared_ptr of Task and shared_ptr to a threadsafe queue and
		 * adds this pair into the task_queue.
		 */
		virtual void submit(std::pair<std::shared_ptr<Task>,return_queue>) = 0;
		virtual ~ThreadPool() {}
	};

	/*
	 *GraphExecutorFactory generates implementations of the above interfaces.
	 */
	class GraphExecutorFactory {
	public:
		static std::shared_ptr<ThreadSafeQueue<std::shared_future<std::shared_ptr<Task>>>> newSingleLockQueue();
		static std::shared_ptr<TaskPoolExecutor> newQueueTaskExecutor();
		static std::shared_ptr<GraphExecutor> newKhansGraphExecutor();
		static std::shared_ptr<ThreadPool> newSingletonThreadPool();
	};
}

#endif /* GRAPHEXECUTOR_H_ */
