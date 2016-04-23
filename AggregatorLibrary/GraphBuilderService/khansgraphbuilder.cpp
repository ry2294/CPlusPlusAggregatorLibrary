#include "graphbuilder.h"

using namespace std;
using namespace GraphBuilderService;

class KhansGraphBuilder : public Graph {
public:
	void addVertex(shared_ptr<Runnable> vertex) {
	}

	void constructGraph() {
	}

	bool isGraphCyclic() {
		return true;
	}
};
