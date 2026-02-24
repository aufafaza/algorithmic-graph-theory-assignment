#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <unordered_map>
#include <vector> 
#include <raylib.h> 
using namespace std; 

struct NodeProperties {
	Vector2 position; 
	Vector2 velocity; 
}; 

class Graph { 
	// adjacency matrix to store edges 
public: 
	Graph(size_t initial_nodes = 0); 
	void addEdge(int u, int v); 
	void addVertex(int u); 
	void BFS(int startNode); 
	void DFS(int startNode);
	// visualizer 
	void printGraph(); 
	void updatePhysics(float deltaTime); 
	void draw(); 
private: 
	// data member 
	std::unordered_map<int, std::vector<int>> adj; 
	std::unordered_map<int, NodeProperties> nodes; 

	float repulsionStrength = 5000.0f; 
	float springStrength = 0.1f; 
	float damping = 0.85f; 
};


#endif 
