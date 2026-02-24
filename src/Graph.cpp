#include "Graph.hpp"
#include <raymath.h> 
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


/* Visualizer related code */
void Graph::updatePhysics(float deltaTime){ 
	for (auto& [id1, p1] : nodes) { 
		Vector2 totalForce = {0, 0}; 
		for (auto& [id2, p2] : nodes) {
			if (id1==id2) continue; 

			Vector2 dir = Vector2Subtract(p1.position, p2.position);
			float distSq = Vector2LengthSqr(dir) + 0.1f; 
			float force = repulsionStrength / distSq; 
			totalForce = Vector2Add(totalForce, Vector2Scale(Vector2Normalize(dir), force)); 
		}
		for (int neighbor : adj[id1]) { 
			Vector2 dir = Vector2Subtract(nodes[neighbor].position, p1.position); 
			float dist = Vector2Length(dir); 
			float force = dist * springStrength;
			totalForce = Vector2Add(totalForce, Vector2Scale(Vector2Normalize(dir), force)); 
		}
		p1.velocity = Vector2Scale(Vector2Add(p1.velocity, totalForce), damping); 
		p1.position = Vector2Add(p1.position, Vector2Scale(p1.velocity, deltaTime)); 
	}
	

	for (auto const& [u, neighbors] : adj) { 
		for (int v : neighbors) { 
			Vector2 delta = Vector2Subtract(nodes[v].position, nodes[u].position);
			float distance = Vector2Length(delta); 

			float restLength = 100.0f; 
			float strength = 0.05f;
			float force = (distance - restLength) * strength; 

			Vector2 attraction = Vector2Scale(Vector2Normalize(delta), force); 

			nodes[u].velocity = Vector2Add(nodes[u].velocity, attraction); 
			nodes[v].velocity = Vector2Subtract(nodes[v].velocity, attraction); 
		}
	}
}

void Graph::draw() { 
	for (auto const& [u, neighbors] : adj) { 
		Vector2 startPos = nodes[u].position; 

		for (int v : neighbors) { 
			Vector2 endPos = nodes[v].position; 
			DrawLineEx(startPos, endPos, 2.0f, DARKGRAY); 
		} 
	}

	for (auto const& [id, prop] : nodes) { 
		DrawCircleV(prop.position, 22.0f, BLACK); 
		DrawCircleV(prop.position, 20.0f, MAROON); 

		std::string label = std::to_string(id); 
		DrawText(label.c_str(), prop.position.x - 8, prop.position.y - 8, 20, WHITE); 
	} 
} 


