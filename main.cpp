#include <iostream> 
#include "include/Graph.hpp"
#include <raylib.h>
int main(){
	Graph g; 
	int s, u, v;
	while (true){ 
		std::cout << "\n1. Add Edge \n2.Add Vertex \n3.BFS \n4.DFS" << std::endl;
		std::cin >> s; 

		if (s == 1){ 
			std::cin >> u >> v; 
			g.addEdge(u, v); 
		} else if (s == 2) { 
			std::cin >> u; 
			g.addVertex(u); 
		} else if (s == 3){ 
			std::cin >> u; 
			std::cout << "BFS Output:" << std::endl; 
			g.BFS(u); 
		} else if (s == 4){ 
			std::cin >> u;
			std::cout << "BFS Output:" << std::endl; 
			g.DFS(u); 
		} else{
			std::cout << "invalid command\n" << std::endl;
			break; 
		} 
	} 
	return 0; 
} 
