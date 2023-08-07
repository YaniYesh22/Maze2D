////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Maze.hpp"
#include <queue>
#include <vector>

class BFSAlgorithm
{
public:
    BFSAlgorithm(Maze &maze);
    std::vector<std::pair<int, int>> findPath(int startRow, int startCol, int endRow, int endCol);

private:
    Maze &maze;
};
