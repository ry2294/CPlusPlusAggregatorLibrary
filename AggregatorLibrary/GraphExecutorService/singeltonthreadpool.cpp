#include "graphexecutor.h"
#include "thread"
#include "singlelockqueue.cpp"
#include "future"

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

template<typename T>
class SingeltonThreadPool : public ThreadPool<T> {
private:
    atomic_bool done;
    unsigned const numThreads;
    SingleLockQueue<T> task_queue;
    vector<thread> threads;
    join_threads joiner;
    static SingeltonThreadPool *thread_pool;
    
    void worker_thread(){
        while(!done){
            T task;
            task=task_queue.wait_and_pop();
            promise<T> promise_value;
            try{
                task->run();
                promise_value.set_value(task);
                //TODO:Pass this value to Completion Service queue
            }
            catch(...){
                promise_value.set_exception(current_exception());
                //TODO:Pass this value to completion service queue
            }
        }
    }
    
    SingeltonThreadPool():
     done(false),joiner(threads) {
        numThreads= std::thread::hardware_concurrency();
        try{
            for(unsigned i=0;i<numThreads;i++){
                threads.push_back(thread(thread_pool->worker_thread));
            }
        }
        catch(...){
            done=true;
            throw;
        } 
    }
    
    ~SingeltonThreadPool(){
        done=true;
    }
    

public:
    void set_numThreads(unsigned nthreads){
        numThreads=nthreads;
    }
    
    SingeltonThreadPool* getInstance(){
        if(!thread_pool){
            thread_pool= new SingeltonThreadPool();
        }
        return thread_pool;
    }
    
    void destroy(){
        delete thread_pool;
        thread_pool = NULL; // Should I set NULL or nullptr.    
    }
    
    void submit(T task){
        task_queue.push(task);
    }
};
