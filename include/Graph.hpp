#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <unordered_map>
#include <vector> 

using namespace std; 

class Graph { 
	// adjacency matrix to store edges 
public: 
	Graph(size_t initial_nodes = 0); 
	void addEdge(int u, int v); 
	void addVertex(int u); 
	void BFS(int startNode); 
	void DFS(int startNode);
private: 
	// data member 
	std::unordered_map<int, std::vector<int>> adj; 
};


#endif 
