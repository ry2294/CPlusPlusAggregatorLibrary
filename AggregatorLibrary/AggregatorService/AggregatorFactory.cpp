#include "aggregator.h"
#include "fixedthreadpoolaggregator.cpp"

using namespace AggregatorService;

shared_ptr<Aggregator> AggregatorFactory::newFixedThreadPoolAggregator() {
	shared_ptr<Aggregator> aggregator (new FixedThreadPoolAggregator());
	return aggregator;
}
