#ifndef AGGREGATOR_H_
#define AGGREGATOR_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <exception>

using namespace std;

namespace AggregatorService {
	class Runnable{
	public:
		virtual string getLabel() const = 0;
		virtual unordered_set<string> getDependencies() const = 0;
		virtual void run(unordered_map<string, Runnable>) = 0;
		virtual ~Runnable() {}
	};

	class Aggregator {
	public:
		virtual void addNode(shared_ptr<Runnable>) = 0;
		virtual void execute() = 0;
		virtual ~Aggregator() {}
	};

	class AggregatorFactory {
	public:
		AggregatorFactory() = delete;
		static shared_ptr<Aggregator> newFixedThreadPoolAggregator();
	};

	class CyclicDependencyFoundException : public exception {
		const char* what() const throw() {
			return "Dependency graph contains cyclic dependency";
		}
	};
}

#endif /* AGGREGATOR_H_ */
