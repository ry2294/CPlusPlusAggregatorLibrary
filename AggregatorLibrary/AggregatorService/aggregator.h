#ifndef AGGREGATOR_H_
#define AGGREGATOR_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <exception>

namespace AggregatorService {
	class Runnable{
	public:
		virtual std::string getLabel() const = 0;
		virtual std::unordered_set<std::string> getDependencies() const = 0;
		virtual void run(std::unordered_map<std::string, std::shared_ptr<Runnable>>) = 0;
		virtual ~Runnable() {}
	};

	class Aggregator {
	public:
		virtual void addNode(std::shared_ptr<Runnable>) = 0;
		virtual void execute() = 0;
		virtual ~Aggregator() {}
	};

	class AggregatorFactory {
	public:
		AggregatorFactory() = delete;
		static std::shared_ptr<Aggregator> newFixedThreadPoolAggregator();
	};

	class CyclicDependencyFoundException : public std::exception {
		const char* what() const throw() {
			return "Dependency graph contains cyclic dependency";
		}
	};
}

#endif /* AGGREGATOR_H_ */
