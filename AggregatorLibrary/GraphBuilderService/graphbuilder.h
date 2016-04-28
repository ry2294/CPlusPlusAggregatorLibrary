#ifndef GRAPHBUILDER_H_
#define GRAPHBUILDER_H_

#include "aggregator.h"
#include <unordered_set>
#include <string>
#include <queue>

namespace GraphBuilderService {
	using namespace AggregatorService;

	/**
	 * Represents the Task wrapper class that the aggregator library uses to wrap a Client's task.
	 */
	class Task {
		public:
			Task(std::shared_ptr<Runnable>);
			std::unordered_set<std::string> getInDegree();
			void addInDegree(std::string, std::shared_ptr<Runnable>);
			void removeInDegree(std::string);
			bool isInDegreeEmpty();
			std::unordered_set<std::string> getOutDegree();
			void addOutDegree(std::string);
			std::shared_ptr<Runnable> getNode();
			std::string getLabel();
			void run();
			~Task();
		private:
			std::shared_ptr<Runnable> node;
			std::unordered_map<std::string, std::shared_ptr<Runnable>> dependencies;
			std::unordered_set<std::string> indegree;
			std::unordered_set<std::string> outdegree;
	};

	/**
	 *Represents the GraphBuilder interface which will be used by Aggregtors to create a Graph and construct edges.
	 */
	class GraphBuilder {
	public:
		/*
		 * Adds a vertex to the graph where the vertex is a Task instance which wraps the input Runnable node passed by the caller.
		 * */
		virtual void addVertex(std::shared_ptr<Runnable>) = 0;
		/*
		 * Constructs edges between the vertices by traversing each vertex and processing its dependencies.
		 * */
		virtual void constructGraph() = 0;
		/*
		 * Checks whether the constructed graph is cyclis.
		 * */
		virtual bool isGraphCyclic() = 0;
		/*
		 * Returns a Task matching the input label.
		 * */
		virtual std::shared_ptr<Task> getTask(std::string) = 0;
		/*
		 * Returns a queue of all the independent tasks which don't have any dependencies.
		 * */
		virtual std::queue<std::shared_ptr<Task>> getIndependentTasks() = 0;
		/*
		 * Returns the size of the constructed graph.
		 * */
		virtual int size() = 0;
		virtual ~GraphBuilder() {}
	};

	/**
	 *Factory for generating Graph builders
	 */
	class GraphBuilderFactory {
	public:
		GraphBuilderFactory() = delete;
		static std::shared_ptr<GraphBuilder> newKhansGraphBuilder();
	};
}

#endif /* GRAPHBUILDER_H_ */
