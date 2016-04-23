#include "graphbuilder.h"
#include "khansgraphbuilder.cpp"

using namespace std;
using namespace GraphBuilderService;

shared_ptr<Graph> GraphBuilderFactory::newKhansGraphBuilder() {
	shared_ptr<Graph> graph (new KhansGraphBuilder());
	return graph;
}

