#include "aggregator.h"
#include "graphbuilder.h"

using namespace std;
using namespace AggregatorService;
using namespace GraphBuilderService;

class FixedThreadPoolAggregator : public Aggregator {
private:
	shared_ptr<Graph> graph;
public:
	FixedThreadPoolAggregator() : graph(GraphBuilderFactory::newKhansGraphBuilder()) {
	}

	void addNode(shared_ptr<Runnable> node) {
		graph->addVertex(node);
	}

	void execute() {
		graph->constructGraph();
		// add executor code
	}

	~FixedThreadPoolAggregator() {
	}
};
