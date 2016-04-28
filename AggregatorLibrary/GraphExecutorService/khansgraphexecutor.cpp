#include "graphexecutor.h"
#include <queue>

using namespace std;
using namespace GraphExecutorService;

class KhansGraphExecutor : public GraphExecutor {
private:
	shared_ptr<TaskPoolExecutor> taskPoolExecutor;
public:
	KhansGraphExecutor() : taskPoolExecutor{GraphExecutorFactory::newQueueTaskExecutor()}{
	}
	void execute(shared_ptr<GraphBuilder> graph) {
		queue<shared_ptr<Task>> independentTasks = graph->getIndependentTasks();
		while(!independentTasks.empty()) {
			shared_ptr<Task> task = independentTasks.front();
			taskPoolExecutor->submit(task);
			independentTasks.pop();
		}
		for(int count = 0; count < graph->size(); count++) {
			shared_ptr<Task> sourceTask = taskPoolExecutor->take();
			unordered_set<string> outDegree = sourceTask->getOutDegree();
			for(auto it = outDegree.begin(); it != outDegree.end(); it++) {
				shared_ptr<Task> destTask = graph->getTask(*it);
				destTask->removeInDegree(sourceTask->getLabel());
				if(destTask->isInDegreeEmpty())
					taskPoolExecutor->submit(destTask);
			}
		}
	}
	~KhansGraphExecutor() {}
};
