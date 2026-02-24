#include "Graph.hpp"
#include <iostream> 

Graph::Graph(size_t initial_nodes) : adj() {
	if (initial_nodes > 0) {
		adj.reserve(initial_nodes);
	} 
} 

void Graph::addVertex(int u) { 
	if (adj.find(u) == adj.end()) { 
		adj[u] = std::vector<int>();
	} 
} 

void Graph::addEdge(int u, int v){
	// check whether vertex exists or not yet 
	if (adj.find(u) == adj.end()) { 
		addVertex(u);
	}

	if (adj.find(v) == adj.end()){
		addVertex(v); 
	} 

	adj[u].push_back(v); 
	adj[v].push_back(u); 
}




