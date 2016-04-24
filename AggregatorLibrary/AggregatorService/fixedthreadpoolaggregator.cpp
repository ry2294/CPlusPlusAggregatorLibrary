#include "aggregator.h"
#include "graphbuilder.h"
#include "graphexecutor.h"

using namespace std;
using namespace AggregatorService;
using namespace GraphBuilderService;
using namespace GraphExecutorService;

class FixedThreadPoolAggregator : public Aggregator {
private:
	shared_ptr<Graph> graph;
	shared_ptr<GraphExecutor> graphExecutor;
public:
	FixedThreadPoolAggregator() : graph(GraphBuilderFactory::newKhansGraphBuilder()),
		graphExecutor(GraphExecutorFactory::newKhansGraphExecutor()){
	}

	void addNode(shared_ptr<Runnable> node) {
		graph->addVertex(node);
	}

	void execute() {
		graph->constructGraph();
		if(graph->isGraphCyclic()) {
			throw CyclicDependencyFoundException{};
		}
		graphExecutor->execute(graph);
	}

	~FixedThreadPoolAggregator() {
	}
};
