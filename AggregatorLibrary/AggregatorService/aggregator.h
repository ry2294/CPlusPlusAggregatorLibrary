#ifndef AGGREGATOR_H_
#define AGGREGATOR_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <exception>

namespace AggregatorService {

	/*
	 * Represents the interface that clients have to implement for each task.
	 * */
	class Runnable{
	public:
		virtual std::string getLabel() const = 0;
		virtual std::unordered_set<std::string> getDependencies() const = 0;
		virtual void run(std::unordered_map<std::string, std::shared_ptr<Runnable>>) = 0;
		virtual ~Runnable() {}
	};

	/*
	 * Exception thrown by Aggregator when the dependency graph is Cyclic.
	 * */
	class CyclicDependencyFoundException : public std::exception {
		const char* what() const throw() {
			return "Dependency graph contains cyclic dependency";
		}
	};

	/*
	 * Represents the Aggregator Interface which will used by clients to interact with the Aggregator Library.
	 * */
	class Aggregator {
	public:
		virtual void addNode(std::shared_ptr<Runnable>) = 0;
		virtual void execute() throw(CyclicDependencyFoundException) = 0;
		virtual ~Aggregator() {}
	};

	/*
	 * Represents the Factory which will be generate aggregators depending on the client's use-case.
	 * */
	class AggregatorFactory {
	public:
		AggregatorFactory() = delete;
		static std::shared_ptr<Aggregator> newFixedThreadPoolAggregator();
	};
}

#endif /* AGGREGATOR_H_ */
