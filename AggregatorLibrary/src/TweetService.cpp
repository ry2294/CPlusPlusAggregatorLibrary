//============================================================================
// Name        : AggregatorLibrary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "aggregator.h"
using namespace std;
using namespace AggregatorService;

void test(int* i) {
	(*i)++;
}

int main() {
	shared_ptr<Aggregator> aggregator = AggregatorFactory::newFixedThreadPoolAggregator();
	int i {0};
	test(&i);
	cout << i << endl;
	return 0;
}
