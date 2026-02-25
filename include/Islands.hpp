#ifndef ISLANDS_HPP 
#define ISLANDS_HPP 

#include <unordered_map>
#include <vector> 
#include <raylib.h> 

void dfs(std::vector<std::vector<char>>& grid, int r, int c, std::vector<std::vector<bool>>& visited);
int numIslands(std::vector<std::vector<char>>& grid);
void island();


#endif 
