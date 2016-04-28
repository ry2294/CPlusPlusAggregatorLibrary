#ifndef AGGREGATOR_H_
#define AGGREGATOR_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <exception>

namespace AggregatorService {

	/**
	 * Represents the interface that clients have to implement for each task.
	 * They should override the getLabel, getDependencies and run functions.
	 * The Aggregator will take the implemented class, draw the dependency graph and will execute the task.
	 */
	class Runnable{
	public:
		/**
		 * The getLabel is a const function returns the name of the task. The user can set anyname for the class,
		 * but would recommend setting it the actual name of the class. This function would be internally 
		 * used while constructing and executing the graph.
		 */
		virtual std::string getLabel() const = 0;
		
		/**
		 * The getDependencies function is used to get the set of dependencies of the node.
		 * The user has to return an unordered_set of std::string specifying the labels of all
		 * the classes on which this class depends upon. 
		 */
		virtual std::unordered_set<std::string> getDependencies() const = 0;
		
		/**
		 * The run method gets an unordered_map of the task labels and the objects as input. 
		 * This input is internally provided by the Aggregator, the map contains the labels 
		 * and objects of the tasks on which this task is dependent on.
		 * The user writes his user code which has to be implemented for this task inside the run, function.
		 **/
		virtual void run(std::unordered_map<std::string, std::shared_ptr<Runnable>>) = 0;
		virtual ~Runnable() {}
	};

	/**
	 * Exception thrown by Aggregator when the dependency graph is Cyclic.
	 */
	class CyclicDependencyFoundException : public std::exception {
		const char* what() const throw() {
			return "Dependency graph contains cyclic dependency";
		}
	};

	/**
	 * Represents the Aggregator Interface which will used by clients to interact with the Aggregator Library.
	 * */
	class Aggregator {
	public:
		/**
		 * The addNode function is used to add a node/task into the graph. The user passes the shared_ptr of 
		 * the task which he wants to add to the graph. The function takes the task and adds it into the dependency graph.
		 */
		virtual void addNode(std::shared_ptr<Runnable>) = 0;
		
		/**
		 * The execute function is used to process the graph and run the tasks added to the graph.
		 * The user can the execute function whenever he wants to run the Aggregator.
		 */
		virtual void execute() throw(CyclicDependencyFoundException) = 0;
		virtual ~Aggregator() {}
	};

	/**
	 * Represents the Factory which will be generate aggregators depending on the client's use-case.
	 */
	class AggregatorFactory {
	public:
		AggregatorFactory() = delete;
		static std::shared_ptr<Aggregator> newFixedThreadPoolAggregator();
	};
}

#endif /* AGGREGATOR_H_ */
