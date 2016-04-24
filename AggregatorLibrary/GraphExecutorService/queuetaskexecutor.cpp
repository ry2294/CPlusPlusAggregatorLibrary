#include "graphexecutor.h"

using namespace std;
using namespace GraphExecutorService;

class QueueTaskExecutor : public TaskPoolExecutor {
public:
	void submit(shared_ptr<Task> task) {
	}

	shared_ptr<Task> take() {
		return nullptr;
	}

	~QueueTaskExecutor(){
	}
};
