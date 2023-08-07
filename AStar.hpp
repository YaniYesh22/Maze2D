// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <vector>
#include <queue> // Include the <queue> header for priority_queue
#include <cmath>
#include "Maze.hpp"

class AStarAlgorithm
{
public:
    AStarAlgorithm(Maze &maze) : maze(maze) {}

    std::vector<std::pair<int, int>> findPath(int startRow, int startCol, int endRow, int endCol);

private:
    Maze &maze;

    struct Node
    {
        int row;
        int col;
        int f; // f = g + h, where g is the cost to reach this node from the start, and h is the estimated cost to the goal.
        int g; // Cost from start to this node
        int h; // Heuristic estimate to the goal

        bool operator>(const Node &other) const
        {
            return f > other.f;
        }
    };

    int heuristic(int row, int col, int endRow, int endCol);
};
