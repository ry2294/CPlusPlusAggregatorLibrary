#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

namespace AggregatorService {
	class Runnable{
	public:
		string getLabel() const = 0;
		unordered_set<string> getDependencies() const = 0;
		void run(unordered_map<string, Runnable>) = 0;
		virtual ~Runnable() {}
	};

	class Aggregator {
	public:
		void addNode(shared_ptr<Runnable>);
		void execute();
	};

	class AggregatorFactory {
	public:
		static Aggregator newFixedThreadPoolAggregator();
	};
}
