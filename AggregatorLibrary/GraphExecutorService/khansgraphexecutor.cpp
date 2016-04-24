#include "graphexecutor.h"

using namespace std;
using namespace GraphExecutorService;

class KhansGraphExecutor : public GraphExecutor {
private:
	shared_ptr<TaskPoolExecutor> taskPoolExecutor;
public:
	KhansGraphExecutor() : taskPoolExecutor{GraphExecutorFactory::newQueueTaskExecutor()}{
	}
	void execute(shared_ptr<Graph> graph) {
	}
	~KhansGraphExecutor() {}
};
