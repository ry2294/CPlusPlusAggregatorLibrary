#include "graphexecutor.h"

using namespace std;
using namespace GraphExecutorService;

class QueueTaskExecutor : public TaskPoolExecutor {
private:
	queue<shared_ptr<Task>> tasksQueue;
public:
	QueueTaskExecutor() : tasksQueue{} {
	}
	void submit(shared_ptr<Task> task) {
		tasksQueue.push(task);
	}

	shared_ptr<Task> take() {
		shared_ptr<Task> task = tasksQueue.front();
		task->run();
		tasksQueue.pop();
		return task;
	}

	~QueueTaskExecutor(){
	}
};
