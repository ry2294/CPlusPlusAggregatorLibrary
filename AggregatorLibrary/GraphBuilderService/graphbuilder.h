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
			Task(shared_ptr<Runnable>);
			unordered_set<string> getInDegree();
			void addInDegree(string, shared_ptr<Runnable>);
			void removeInDegree(string);
			bool isInDegreeEmpty();
			unordered_set<string> getOutDegree();
			void addOutDegree(string);
			void run();
			~Task();
		private:
			shared_ptr<Runnable> node;
			unordered_map<string, shared_ptr<Runnable>> dependencies;
			unordered_set<string> indegree;
			unordered_set<string> outdegree;
	};
}

#endif /* GRAPHBUILDER_H_ */
