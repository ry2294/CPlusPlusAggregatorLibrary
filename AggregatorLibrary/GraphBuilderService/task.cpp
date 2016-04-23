#include "graphbuilder.h"

using namespace std;
using namespace GraphBuilderService;

Task::Task(shared_ptr<Runnable> node) : node{node}, dependencies{}, indegree{}, outdegree{}{
}

unordered_set<string> Task::getInDegree() {
	return Task::indegree;
}

void Task::addInDegree(string nodeLabel, shared_ptr<Runnable> node) {
	Task::indegree.insert(nodeLabel);
	Task::dependencies.insert({nodeLabel, node});
}

void Task::removeInDegree(string nodeLabel) {
	Task::indegree.erase(nodeLabel);
}

bool Task::isInDegreeEmpty() {
	return Task::indegree.empty();
}

unordered_set<string> Task::getOutDegree() {
	return Task::outdegree;
}

void Task::addOutDegree(string nodeLabel) {
	Task::outdegree.insert(nodeLabel);
}

void Task::run() {
	Task::node->run(Task::dependencies);
}
