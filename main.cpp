#include "include/Graph.hpp"
#include "include/Islands.hpp"
#include <iostream>
#include <thread>
#include <raylib.h>
#include <fstream>

void CLI_Interface(Graph& g, const std::string& filename) {

    if (!filename.empty()) {
        std::string filepath = "./tests/"+ filename;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filename << "\n";
        } else {

            int cmd, u, v;

            while (file >> cmd) {
                switch (cmd) {
                    case 1: 
                        if (file >> u >> v)
                            g.addEdge(u, v);
                        break;

                    case 2: 
                        if (file >> u)
                            g.addVertex(u);
                        break;

                    default:
                        std::cout << "Unknown command in file.\n";
                }
            }

            std::cout << "Graph loaded from file: " << filename << "\n";
        }
    }

    int s, u, v;
    while (true) {
        std::cout << "\n--- Graph Menu ---\n";
        std::cout << "1. Add Edge (u v)\n2. Add Vertex (u)\n3. Visual BFS (start)\n4. Visual DFS (start)\n";
        std::cout << "5. Path Check (u v)\n6. Component Analysis\n7. Reset Colors\n8. Find Islands\n0. Exit\nChoice: ";
        
        if (!(std::cin >> s) || s == 0) break;

        switch(s) {
            case 1:
                std::cin >> u >> v;
                g.addEdge(u, v);
                break;
            case 2:
                std::cin >> u;
                g.addVertex(u);
                break;
            case 3:
                std::cin >> u;
                g.visualBFS(u); 
                break;
            case 4:
                std::cin >> u;
                g.visualDFS(u);
                break;
            case 5:
                std::cin >> u >> v;
                if (g.hasPath(u, v)) std::cout << "Path exists!\n";
                else std::cout << "No path found.\n";
                break;
            case 6:
                g.component();
                break;
            case 7:
                break;
            case 8:
                island();
                break;
            default:
                std::cout << "Invalid command.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Graph Physics Visualizer");
    SetTargetFPS(60);

    Graph g;

    std::string filename = (argc == 2) ? argv[1] : "";

    if(argc > 2){
        std::cout << "Invalid! Run by './GraphSolver' or './GraphSolver graph.txt'";
        return 0;
    }

    std::thread inputThread(CLI_Interface, std::ref(g), filename);
    inputThread.detach();

    while (!WindowShouldClose()) {
        g.updatePhysics(GetFrameTime());
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            g.draw();
            
            DrawRectangle(10, 10, 320, 60, Fade(SKYBLUE, 0.5f));
            DrawText("Interact via Terminal", 20, 20, 20, DARKBLUE);
            DrawText("Nodes repel, Edges pull (Springs)", 20, 45, 15, BLACK);
	    DrawFPS(720, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0; 
}
