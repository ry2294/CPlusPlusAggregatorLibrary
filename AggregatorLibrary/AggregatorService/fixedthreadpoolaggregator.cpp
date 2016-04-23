#include "aggregator.h"

using namespace std;
using namespace AggregatorService;

class FixedThreadPoolAggregator : public Aggregator {
public:
	FixedThreadPoolAggregator() {
	}

	void addNode(shared_ptr<Runnable> node) {
	}

	void execute() {
	}

	~FixedThreadPoolAggregator() {
	}
};
