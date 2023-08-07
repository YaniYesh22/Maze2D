// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AStar.hpp"

int AStarAlgorithm::heuristic(int row, int col, int endRow, int endCol)
{
    return std::abs(row - endRow) + std::abs(col - endCol);
}

std::vector<std::pair<int, int>> AStarAlgorithm::findPath(int startRow, int startCol, int endRow, int endCol)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<std::vector<bool>> visited(maze.getNumRows(), std::vector<bool>(maze.getNumCols(), false));
    std::vector<std::vector<Node>> nodes(maze.getNumRows(), std::vector<Node>(maze.getNumCols()));

    openList.push({startRow, startCol, 0, 0, heuristic(startRow, startCol, endRow, endCol)});
    nodes[startRow][startCol] = {startRow, startCol, 0, 0, heuristic(startRow, startCol, endRow, endCol)};

    static const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

    while (!openList.empty())
    {
        Node current = openList.top();
        openList.pop();

        int row = current.row;
        int col = current.col;

        if (row == endRow && col == endCol)
        {
            // Path found, reconstruct and return it
            std::vector<std::pair<int, int>> path;
            while (row != startRow || col != startCol)
            {
                path.push_back({row, col});
                Node parent = nodes[row][col];
                row = parent.row;
                col = parent.col;
            }
            path.push_back({startRow, startCol});
            std::reverse(path.begin(), path.end());
            return path;
        }

        visited[row][col] = true;

        for (int dir = 0; dir < 4; ++dir)
        {
            int newRow = row + directions[dir][0];
            int newCol = col + directions[dir][1];

            if (maze.isValidMoveWall(row, col, dir) && maze.isValidMove(newRow, newCol) && !visited[newRow][newCol])
            {
                int newG = current.g + 1;
                int newH = heuristic(newRow, newCol, endRow, endCol);
                int newF = newG + newH;

                if (nodes[newRow][newCol].f == 0 || newF < nodes[newRow][newCol].f)
                {
                    openList.push({newRow, newCol, newF, newG, newH});
                    nodes[newRow][newCol] = {newRow, newCol, newF, newG, newH};
                }
            }
        }
    }

    // No path found
    return std::vector<std::pair<int, int>>();
}