#include "graphbuilder.h"
#include <queue>

using namespace std;
using namespace GraphBuilderService;

class KhansGraphBuilder : public Graph {
private:
	unordered_map<string, shared_ptr<Task>> adjacencyMap;
	unordered_map<string, unordered_set<string>> inDegrees;
	unordered_map<string, unordered_set<string>> outDegrees;
public:
	KhansGraphBuilder() : adjacencyMap{}, inDegrees{}, outDegrees{} {
	}

	void addVertex(shared_ptr<Runnable> vertex) {
		adjacencyMap.insert({vertex->getLabel(), shared_ptr<Task>(new Task(vertex))});
		inDegrees.insert({vertex->getLabel(), {}});
		outDegrees.insert({vertex->getLabel(), {}});
	}

	void constructGraph() {
		for(auto it = adjacencyMap.begin(); it != adjacencyMap.end(); it++) {
			shared_ptr<Task> destTask = it->second;
			shared_ptr<Runnable> destNode = destTask->getNode();
			unordered_set<string> dependencies = destNode->getDependencies();
			for(string label : dependencies) {
				auto adjMapSearch = adjacencyMap.find(label);
				if(adjMapSearch != adjacencyMap.end()) {
					shared_ptr<Task> sourceTask = adjMapSearch->second;
					shared_ptr<Runnable> sourceNode = sourceTask->getNode();
					destTask->addInDegree(sourceNode->getLabel(), sourceNode);
					sourceTask->addOutDegree(destNode->getLabel());
					auto inDegreeSearch = inDegrees.find(destNode->getLabel());
					if(inDegreeSearch != inDegrees.end()) {
						unordered_set<string>& dependencies = inDegreeSearch->second;
						dependencies.insert(sourceNode->getLabel());
					}
					auto outDegreeSearch = outDegrees.find(sourceNode->getLabel());
					if(outDegreeSearch != outDegrees.end()) {
						unordered_set<string>& dependents = outDegreeSearch->second;
						dependents.insert(destNode->getLabel());
					}
				}
			}
		}
	}

	bool isGraphCyclic() {
		int visitedVertices = 0;
		queue<string> tasksQueue;
		for(auto it = inDegrees.begin(); it != inDegrees.end(); it++) {
			unordered_set<string>& dependencies = it->second;
			if(dependencies.empty())
				tasksQueue.push(it->first);
		}
		while(!tasksQueue.empty()) {
			string nodeLabel = tasksQueue.front();
			auto outDegreeSearch = outDegrees.find(nodeLabel);
			if(outDegreeSearch != outDegrees.end()) {
				unordered_set<string>& dependents = outDegreeSearch->second;
				for(auto outDegIt = dependents.begin(); outDegIt != dependents.end(); outDegIt++) {
					auto inDegreeSearch = inDegrees.find(*outDegIt);
					if(inDegreeSearch != inDegrees.end()) {
						unordered_set<string>& dependencies = inDegreeSearch->second;
						dependencies.erase(nodeLabel);
						if(dependencies.empty())
							tasksQueue.push(inDegreeSearch->first);
					}
				}
			}
			tasksQueue.pop();
			visitedVertices++;
		}
		return visitedVertices != adjacencyMap.size();
	}
};
