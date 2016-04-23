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

	class Task {
		public:
			virtual unordered_set<string> getInDegree() = 0;
			virtual void addInDegree(string) = 0;
			virtual void removeInDegree(string) = 0;
			virtual bool isInDegreeEmpty() = 0;
			virtual unordered_set<string> getOutDegree() = 0;
			virtual void addOutDegree(string) = 0;
			virtual shared_ptr<Runnable> getNode() = 0;
			virtual void run() = 0;
			virtual ~Task() {}
	};
}

#endif /* GRAPHBUILDER_H_ */
