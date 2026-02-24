#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <stack> 

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

void Graph::DFS(int startNode){ 
	std::unordered_map<int, bool> visited; 
	std::stack<int> q; 

	visited[startNode] = true; 
	q.push(startNode); 
	

	while (!q.empty()) { 
		int current = q.top(); 
		q.pop(); 
		std::cout << current << std::endl; 

		for (int neighbor : adj[current]){ 
			if (!visited[neighbor]){ 
				visited[neighbor] = true; 
				q.push(neighbor); 
			}
		}
	}
} 

void Graph::BFS(int startNode){ 
	std::unordered_map<int, bool> visited; 
	std::queue<int> q; 

	visited[startNode] = true; 
	q.push(startNode); 

	while (!q.empty()){ 
		int current = q.front(); 
		q.pop(); 
		std::cout << current << std::endl; 

		for (int neighbor : adj[current]){
			if (!visited[neighbor]){
				visited[neighbor] = true; 
				q.push(neighbor); 
			} 
		} 
	} 
} 

