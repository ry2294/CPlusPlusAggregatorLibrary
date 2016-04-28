#include "graphbuilder.h"
#include "khansgraphbuilder.cpp"

using namespace std;
using namespace GraphBuilderService;

shared_ptr<GraphBuilder> GraphBuilderFactory::newKhansGraphBuilder() {
	shared_ptr<GraphBuilder> graph (new KhansGraphBuilder());
	return graph;
}

