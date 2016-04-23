//============================================================================
// Name        : AggregatorLibrary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "aggregator.h"
#include <unordered_set>
using namespace std;
using namespace AggregatorService;

class TestHashSet {
private:
	unordered_set<string> strings;
public:
	void addTasks(string s) {
		strings.insert(s);
	}
	unordered_set<string> getTasks() {
		return strings;
	}
	void printTasks() {
		for(auto s : strings) {
			cout << s << endl;
		}
	}
};

int main() {
	TestHashSet obj;
	obj.addTasks("a");
	obj.addTasks("b");
	obj.addTasks("c");
	unordered_set<string> strings = obj.getTasks();
	strings.insert("d");
	obj.printTasks();
	for(auto s : strings) {
		cout << s << endl;
	}
	return 0;
}
