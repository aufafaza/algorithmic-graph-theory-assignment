#include "Graph.hpp"
#include <ctime>
#include <raymath.h> 
#include <iostream>
#include <queue>
#include <stack> 
#include <chrono>
#include <thread> 
#include <string>
Graph::Graph(size_t initial_nodes) : adj() {
	if (initial_nodes > 0) {
		adj.reserve(initial_nodes);
	} 
} 

void Graph::addVertex(int u) { 
	if (adj.find(u) == adj.end()) { 
		adj[u] = std::vector<int>();
		
		float rx = 400 + GetRandomValue(-100, 100);
		float ry = 300 + GetRandomValue(-100, 100);
        
		nodes[u] = { {rx, ry}, {0, 0} };
	}
	simulationActive = true;

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
	simulationActive = true;
}

std::unordered_map<int, bool> Graph::DFS(int startNode){ 
	std::unordered_map<int, bool> visited; 
	std::stack<int> q; 

	q.push(startNode); 	

	while (!q.empty()) { 
		int current = q.top(); 
		q.pop(); 
		
		if (visited.find(current) == visited.end()){
			visited[current] = true; 

			std::cout << current << std::endl; 

			if (nodes.count(current)) { 
				nodes[current].color = ORANGE; 
			} 

			std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

			for (int neighbor : adj[current]){
				if (visited.find(neighbor) == visited.end()){
					q.push(neighbor);
				}
			}
		}
	}
	return visited;
} 
std::unordered_map<int, bool>  Graph::BFS(int startNode){ 
	std::unordered_map<int, bool> visited; 
	std::queue<int> q; 

	visited[startNode] = true; 
	q.push(startNode); 

	while (!q.empty()){ 
		int current = q.front(); 
		q.pop(); 
		std::cout << current << std::endl;

		if (nodes.count(current)) { 
			nodes[current].color = GREEN;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		for (int neighbor : adj[current]){
			if (!visited[neighbor]){
				visited[neighbor] = true; 
				q.push(neighbor);
	
			} 
		} 
	}
	return visited;
} 

bool Graph::hasPath(int start, int target) {
	auto visited = BFS(start); 
	return visited.count(target) > 0;
} 

void Graph::component() {
    std::unordered_map<int, bool> globalVisited;
    int componentCount = 0;
    std::vector<int> componentSizes;

    for (auto const& [node, _] : adj) {
        if (!globalVisited[node]) {
            componentCount++;
            auto componentNodes = BFS(node); 
            componentSizes.push_back(componentNodes.size());

	    for (auto const& [id, _] : componentNodes) {
		    globalVisited[id] = true; 
		}
        }
    }

    // Output Results
    std::cout << "Number of components: " << componentCount << std::endl;
    for (int i = 0; i < componentSizes.size(); i++) {
        std::cout << "Component " << i + 1 << " size: " << componentSizes[i] << std::endl;
    }
    std::cout << "Is Connected: " << (componentCount == 1 ? "Yes" : "No") << std::endl;
}
/* Visualizer related code */
void Graph::updatePhysics(float deltaTime){ 
	if (!simulationActive) return; 	
	for (auto& [id1, p1] : nodes) { 
		Vector2 totalForce = {0, 0}; 
		for (auto& [id2, p2] : nodes) {
			if (id1==id2) continue; 

			Vector2 dir = Vector2Subtract(p1.position, p2.position);
			float distSq = Vector2LengthSqr(dir) + 0.1f; 
			float force = repulsionStrength / distSq; 
			totalForce = Vector2Multiply(totalForce, Vector2Scale(Vector2Normalize(dir), force)); 
		}
	
		p1.velocity = Vector2Add(p1.velocity, Vector2Scale(totalForce, deltaTime));
	}
	float restLength = 100.0f; 
	for (auto const& [u, neighbors] : adj)
	{
		for (int v : neighbors)
		{
		    Vector2 delta = Vector2Subtract(
			nodes[v].position,
			nodes[u].position
		    );

		    float distance = Vector2Length(delta);
		    if (distance < 0.001f) continue;

		    float force = (distance - restLength) * springStrength * 2;

		    Vector2 attraction = Vector2Scale(
			Vector2Normalize(delta),
			force
		    );

		    nodes[u].velocity = Vector2Add(
			nodes[u].velocity,
			Vector2Scale(attraction, deltaTime)
		    );

		    nodes[v].velocity = Vector2Subtract(
			nodes[v].velocity,
			Vector2Scale(attraction, deltaTime)
		    );
		}
	    }
	float totalMovement = 0.0f; 
	for (auto& [id, p] : nodes) { 
		p.velocity = Vector2Scale(p.velocity, damping); 

		if (Vector2Length(p.velocity) < 0.01f){ 
			p.velocity = {0, 0};
		} 

		p.position = Vector2Add(p.position, Vector2Scale(p.velocity, deltaTime));
		totalMovement += Vector2Length(p.velocity);
	}
	if (totalMovement < 0.001f){ 
		simulationActive = false;
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
		DrawCircleV(prop.position, 20.0f, prop.color); 

		std::string label = std::to_string(id); 
		DrawText(label.c_str(), prop.position.x - 8, prop.position.y - 8, 20, WHITE); 
	} 
} 

void Graph::resetColors() { 
	for (auto& [id, prop] : nodes) { 
		prop.color = MAROON; 
	} 
} 

void Graph::visualBFS(int startNode) {
	resetColors(); 
	auto visitedMap = BFS(startNode);
    for (auto const& [id, _] : visitedMap) {
        nodes[id].color = GREEN; // Highlight visited nodes
    }
}

void Graph::visualDFS(int startNode) {
    auto visitedMap = DFS(startNode);
    for (auto const& [id, _] : visitedMap) {
        nodes[id].color = GREEN; // Highlight visited nodes
	}
}


