#include "Islands.hpp"
#include <ctime>
#include <raymath.h> 
#include <iostream>
#include <queue>
#include <stack> 
#include <chrono>
#include <thread> 
#include <fstream>

void dfs(std::vector<std::vector<char>>& grid, int r, int c, std::vector<std::vector<bool>>& visited){
	if(r>=0 && r < grid.size() && c>=0 && c < grid[0].size() && !visited[r][c] && grid[r][c] == '1'){
		visited[r][c] = true;
		dfs(grid, r-1, c, visited);
		dfs(grid, r, c-1, visited);
		dfs(grid, r+1, c, visited);
		dfs(grid, r, c+1, visited);
	}
}

int numIslands(std::vector<std::vector<char>>& grid) {
	int n = grid.size();
	int m = grid[0].size();

	std::vector<std::vector<bool>> visited (n, std::vector<bool> (m, false));
	int islands = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (grid[i][j] == '1' && !visited[i][j]){
				dfs(grid, i, j, visited);
				islands++;
			}
		}
	}

	return islands;
}

void island(){
	int n, m;
	std::vector<std::vector<char>> grid;
	std::string s;

	std::cout << "\n=== Count Islands ===\n";
    std::cout << "1. Manual Input\n";
    std::cout << "2. Load from File\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 2) {
    	std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        std::ifstream file("./tests/"+filename);
        if (!file.is_open()) {
            std::cout << "Failed to open file.\n";
            return;
        }

        file >> n >> m;

        for (int i = 0; i < n; i++) {
            file >> s;

            if (s.size() != m) {
                std::cout << "DIMENSION ERROR in file!\n";
                return;
            }

            grid.emplace_back(s.begin(), s.end());
        }

        std::cout << "Map loaded successfully.\n";
    } else{
		std::cout << "== Map dimensions ==\n";
		std::cout << "Map rows: ";
		std::cin >> n;
		std::cout << "Map columns: ";
		std::cin >> m;

		std::cout << "Enter map row per row (1 means land, 0 means water, no spaces):";
		
		for(int i = 0; i < n; i++){
			std::cin >> s;
			if(s.size() != m){
				std::cout << "DIMENSION ERROR! Incorrect column count, please reenter the row.\n";
				i--;
				continue;
			}
			std::vector<char> row(s.begin(), s.end());
			grid.push_back(row);
		} 
	}

	std::cout << "\nNumber of Islands: " << numIslands(grid) << "\n";
}
