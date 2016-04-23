#ifndef GRAPHBUILDER_H_
#define GRAPHBUILDER_H_

#include "aggregator.h"
#include <unordered_set>
#include <string>

using namespace std;
using namespace AggregatorService;

namespace GraphBuilderService {
	class Graph {
	public:
		virtual void addVertex(shared_ptr<Runnable>) = 0;
		virtual void constructGraph() = 0;
		virtual bool isGraphCyclic() = 0;
		virtual ~Graph() {}
	};

	class GraphBuilderFactory {
	public:
		GraphBuilderFactory() = delete;
		static shared_ptr<Graph> newKhansGraphBuilder();
	};
}

#endif /* GRAPHBUILDER_H_ */
