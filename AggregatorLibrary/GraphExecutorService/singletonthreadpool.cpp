#include "graphexecutor.h"
#include <thread>
#include "singlelockqueue.cpp"
#include <future>

using namespace std;
using namespace GraphExecutorService;
class join_threads{
	std::vector<std::thread>& threads;
public:
	explicit join_threads(std::vector<std::thread>& threads_):
		threads(threads_)
	{}
	~join_threads(){
		for(unsigned long i=0;i<threads.size();++i){
			if(threads[i].joinable())
				threads[i].join();
		}
	}
};

class SingeltonThreadPool : public ThreadPool {
private:
    atomic_bool done;
    SingleLockQueue<pair<shared_ptr<Task>, shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>>>> task_queue;
    vector<thread> threads;
    join_threads joiner;

    void worker_thread(){
        while(!done){
        	auto pair = task_queue.wait_and_pop();
        	shared_ptr<Task> task = pair.first;
            promise<shared_ptr<Task>> promise_task;
            try{
                task->run();
                promise_task.set_value(task);
            }
            catch(...){
            	promise_task.set_exception(current_exception());
            }
            auto executor_queue = pair.second;
            executor_queue->push(promise_task.get_future().share());
        }
    }

public:
	SingeltonThreadPool() : done(false),joiner(threads) {
		try{
			for(unsigned i=0; i<std::thread::hardware_concurrency(); i++){
				threads.push_back(thread(&SingeltonThreadPool::worker_thread, this));
			}
		}
		catch(...){
			done=true;
			throw;
		}
	}

    void submit(pair<shared_ptr<Task>, shared_ptr<ThreadSafeQueue<shared_future<shared_ptr<Task>>>>> task){
        task_queue.push(task);
    }

    ~SingeltonThreadPool(){
    	done=true;
    }
};
