////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include "Wall.hpp"

class Cell
{
public:
    Cell();
    bool isVisited() const;
    void markVisited();
    bool isPath() const; // New function added
    Wall upWall, downWall, leftWall, rightWall;
    void clearVisited(); // Add this function to clear the visited state
    bool isWall() const;
    Cell(const Cell &other);
    void setPath(bool isPath); // New function to set whether the cell is part of the path
    int getGScore(){return gScore;};
    bool isWallCell();
    bool setRightWall(bool);
    bool setDownWall(bool);
    bool getRightWall(){return hasRightWall;};
    bool getDownWall(){return hasDownWall;};
private:
    bool visited;
    bool path;
    int fScore = 0; // Total cost (gScore + hScore)
    int gScore = 0; // Cost from start to current cell
    std::pair<int, int> prevCell = {-1, -1};
    bool hasRightWall;
    bool hasDownWall;
};
