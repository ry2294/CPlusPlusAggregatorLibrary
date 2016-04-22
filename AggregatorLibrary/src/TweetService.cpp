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

void test(int* i) {
	(*i)++;
}

int main() {
	int i {0};
	bool changed {false};
	test(&i);
	cout << i << endl;
	return 0;
}
