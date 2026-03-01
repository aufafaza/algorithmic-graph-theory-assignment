#ifndef ISLANDS_HPP 
#define ISLANDS_HPP 

#include <vector> 
#include <string>
#include <raylib.h> 

void dfs(std::vector<std::vector<char>>& grid, int r, int c, std::vector<std::vector<bool>>& visited);
int numIslands(std::vector<std::vector<char>>& grid);
void island();

enum RenderMode { GRAPH_MODE, ISLAND_MODE };
extern RenderMode currentRenderMode;

class IslandGrid { 
public: 
	IslandGrid(); 
	void loadGrid(const std::vector<std::vector<char>>& grid);
	void solve();
	void draw(int screenWidth, int screenHeight);
	bool hasData() const;
	int  getIslandCount() const;
	void clear();
private: 
	std::vector<std::vector<char>> grid;
	std::vector<std::vector<int>>  islandId;
	int rows = 0;
	int cols = 0;
	int islandCount = 0;
	bool solving = false;
	int curR = -1;
	int curC = -1;

	std::vector<Color> islandColors;

	void dfsColor(int r, int c, int id, std::vector<std::vector<bool>>& visited);
	void generateColors();
};

extern IslandGrid g_matrix;

#endif 
