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
		virtual void submit() = 0;
		virtual void take() = 0;
		virtual ~TaskExecutorPool(){}
	};
}

#endif /* GRAPHEXECUTOR_H_ */
