// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Cell.hpp"
#include <memory>
#include "Direction.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Maze
{
public:
    Maze(int rows, int cols, string name);
    ~Maze();
    Maze(const Maze &other);
    void generateMazeRecursive(int row, int col);
    void generateMaze();
    void printMaze(std::ostream &output = std::cout) const; // Add this method to print the maze for testing/debugging
    int getNumRows() const;
    int getNumCols() const;
    Cell &getCell(int row, int col);
    bool isValidMove(int row, int col) const;
    bool isValidMoveWall(int row, int col, int dir);
    bool isValidDirection(int row, int col, int Newrow, int Newcol);
    void updateUserlocation(int userX = 0, int userY = 0);
    string getName();
    void resetCells();
    bool breadthFirstSearch(int startRow, int startCol, int exitRow, int exitCol);
    bool astarSearch(int startRow, int startCol, int exitRow, int exitCol);
    void printMazeWithPath() const;
    void resetPath();
    bool hasPath() const;
    void startGame();
    void setWall(int row, int col, bool hasWall);
    void printMazeFromFile(std::ostream &output) const;
    bool hasRightWall(int row, int col) const;
    bool hasDownWall(int row, int col) const;
    std::string compress();
private:
    int numRows,
        numCols;
    Cell **grid;
    int userRow; // User's current row
    int userCol; // User's current column
    std::string mazeName;
    std::vector<std::vector<std::pair<int, int>>> path; // Add the path vector
};
