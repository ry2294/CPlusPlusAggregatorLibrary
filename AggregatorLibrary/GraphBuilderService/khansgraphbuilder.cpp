#include "graphbuilder.h"

using namespace std;
using namespace GraphBuilderService;

class KhansGraphBuilder : public Graph {
private:
	unordered_map<string, shared_ptr<Task>> adjacencyMap;
public:
	KhansGraphBuilder() : adjacencyMap{} {
	}

	void addVertex(shared_ptr<Runnable> vertex) {

	}

	void constructGraph() {
	}

	bool isGraphCyclic() {
		return true;
	}
};
