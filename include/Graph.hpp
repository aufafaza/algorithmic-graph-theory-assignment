#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <unordered_map>
#include <vector> 

using namespace std; 

class Graph { 
	// adjacency matrix to store edges 
public: 
	Graph(); 
	void AddEdge(int u, int v); 
	void AddVertex(int u); 

private: 
	// data member 
	std::unordered_map<int, std::vector<int>> adj; 
};


#endif 
