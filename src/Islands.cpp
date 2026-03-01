#include "Islands.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <chrono>
#include <thread>

RenderMode currentRenderMode = GRAPH_MODE;
IslandGrid g_matrix;

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

	g_matrix.loadGrid(grid);
	currentRenderMode = ISLAND_MODE;
	g_matrix.solve();

	std::cout << "(Island grid is now shown in the GUI window. "
	          << "Select option 7 in menu to go back to graph view.)\n";
}

IslandGrid::IslandGrid() {}

void IslandGrid::loadGrid(const std::vector<std::vector<char>>& g){
	grid = g;
	rows = grid.size();
	cols = grid[0].size();
	islandId.assign(rows, std::vector<int>(cols, -1));
	islandCount = 0;
	solving = false;
	islandColors.clear();
}

void IslandGrid::dfsColor(int r, int c, int id, std::vector<std::vector<bool>>& visited){
	if(r < 0 || r >= rows || c < 0 || c >= cols) return;
	if(visited[r][c] || grid[r][c] != '1') return;

	visited[r][c] = true;
	islandId[r][c] = id;
	curR = r;
	curC = c;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	dfsColor(r-1, c, id, visited);
	dfsColor(r+1, c, id, visited);
	dfsColor(r, c-1, id, visited);
	dfsColor(r, c+1, id, visited);
}

void IslandGrid::generateColors(){
	islandColors.resize(islandCount);
	for(int i = 0; i < islandCount; i++){
		float hue = fmodf(i * 137.508f, 360.0f);
		islandColors[i] = ColorFromHSV(hue, 0.75f, 0.90f);
	}
}

void IslandGrid::solve(){
	if(rows == 0 || cols == 0) return;
	solving = true;
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
	islandCount = 0;

	generateColors();

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(grid[i][j] == '1' && !visited[i][j]){
				islandCount++;
				generateColors();
				dfsColor(i, j, islandCount - 1, visited);
			}
		}
	}
	solving = false;
	curR = -1;
	curC = -1;
}

bool IslandGrid::hasData() const { return rows > 0 && cols > 0; }
int  IslandGrid::getIslandCount() const { return islandCount; }

void IslandGrid::clear(){
	grid.clear();
	islandId.clear();
	rows = cols = islandCount = 0;
	islandColors.clear();
}

void IslandGrid::draw(int screenWidth, int screenHeight){
	if(!hasData()) return;

	const int padding = 40;
	const int topMargin = 70;
	const int availW = screenWidth - 2 * padding;
	const int availH = screenHeight - topMargin - padding;

	float cellW = (float)availW / cols;
	float cellH = (float)availH / rows;
	float cell = (cellW < cellH) ? cellW : cellH;
	if(cell < 4.0f) cell = 4.0f;

	float gridW = cell * cols;
	float gridH = cell * rows;
	float offsetX = (screenWidth - gridW) / 2.0f;
	float offsetY = topMargin + (availH - gridH) / 2.0f;

	std::string sub = solving
		? "Solving... Islands so far: " + std::to_string(islandCount)
		: "Islands found: " + std::to_string(islandCount);
	int subW = MeasureText(sub.c_str(), 20);
	DrawText(sub.c_str(), (screenWidth - subW) / 2, 20, 20, DARKBLUE);

	Color waterBlue = { 30, 100, 180, 255 };
	Color gridLine = { 0, 0, 0, 60 };
	Color unvisitedLand = { 180, 180, 180, 255 };

	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			float x = offsetX + c * cell;
			float y = offsetY + r * cell;
			Rectangle rect = { x, y, cell, cell };

			if(grid[r][c] == '1'){
				int id = islandId[r][c];
				if(id >= 0 && id < islandColors.size()){
					DrawRectangleRec(rect, islandColors[id]);
				} else{
					DrawRectangleRec(rect, unvisitedLand);
				}
			} else{
				DrawRectangleRec(rect, waterBlue);
			}

			if(solving && r == curR && c == curC){
				Color highlight = { 255, 255, 255, 180 };
				DrawRectangleRec(rect, highlight);
				DrawRectangleLinesEx(rect, 2.0f, WHITE);
			} else{
				DrawRectangleLinesEx(rect, 1.0f, gridLine);
			}
		}
	}
}