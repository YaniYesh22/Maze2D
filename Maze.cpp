// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Maze.hpp"
#include <fstream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>
#include <unordered_set>
#include <memory>
#include <unordered_map>
#include <utility>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include "User.hpp"
#include "Maze2D.hpp"
#include "User.hpp"
#include <cstdlib> // For system()
#include <cstdio>  // For getchar()
#ifdef _WIN32
#include <conio.h> // For _getch() on Windows
#else
#include <termios.h>
#include <unistd.h>
#endif
// Cross-platform getch() function
#ifdef _WIN32
char getch()
{
    return _getch();
}
#else
char getch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif
Maze::Maze(int rows, int cols, std::string mazeName) : numRows(rows), numCols(cols), mazeName(mazeName), userRow(0), userCol(0)
{
    grid = new Cell *[numRows];
    for (int i = 0; i < numRows; ++i)
    {
        grid[i] = new Cell[numCols];
    }
    srand(time(nullptr)); // Seed random number generator with current time
}

Maze::~Maze()
{
    for (int i = 0; i < numRows; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}


// Helper function to get a random direction (0: up, 1: down, 2: left, 3: right)
int getRandomDirection()
{
    return rand() % 4;
}
void Maze::generateMaze()
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            grid[row][col].clearVisited();
        }
    }

    generateMazeRecursive(0, 0);
}

void Maze::generateMazeRecursive(int row, int col)
{
    Cell &currentCell = grid[row][col];
    currentCell.markVisited();

    int directions[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; ++i)
    {
        int randomIndex = i + rand() % (4 - i);
        std::swap(directions[i], directions[randomIndex]);
    }

    for (int i = 0; i < 4; ++i)
    {
        int direction = directions[i];
        int newRow = row, newCol = col;

        if (direction == 0)
        { // Up
            newRow--;
        }
        else if (direction == 1)
        { // Down
            newRow++;
        }
        else if (direction == 2)
        { // Left
            newCol--;
        }
        else if (direction == 3)
        { // Right
            newCol++;
        }

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
            !grid[newRow][newCol].isVisited())
        {
            if (direction == 0)
            {
                currentCell.upWall.remove();
                grid[newRow][newCol].downWall.remove();
            }
            else if (direction == 1)
            {
                currentCell.downWall.remove();
                grid[newRow][newCol].upWall.remove();
            }
            else if (direction == 2)
            {
                currentCell.leftWall.remove();
                grid[newRow][newCol].rightWall.remove();
            }
            else if (direction == 3)
            {
                currentCell.rightWall.remove();
                grid[newRow][newCol].leftWall.remove();
            }

            generateMazeRecursive(newRow, newCol);
        }
    }
}

void Maze::printMaze(std::ostream &output) const
{
    // Print top border
    output << "Maze Name: " << mazeName << endl;
    for (int col = 0; col < numCols; ++col)
    {
        output << "+---";
    }
    output << "+" << std::endl;

    for (int row = 0; row < numRows; ++row)
    {
        // Print cell contents and vertical walls
        for (int col = 0; col < numCols; ++col)
        {
            if (col == 0)
            {
                output << "|";
            }

            if (row == userRow && col == userCol)
            {
                output << " $ "; // Display the user character at their position
            }
            else if (row == 0 && col == 0)
            {
                output << " E ";
            }
            else if (row == numRows - 1 && col == numCols - 1)
            {
                output << " X ";
            }
            else
            {
                output << "   ";
            }

            if (grid[row][col].rightWall.isPresent())
            {
                output << "|";
            }
            else
            {
                output << " ";
            }
        }
        output << std::endl;

        // Print horizontal walls
        output << "+";
        for (int col = 0; col < numCols; ++col)
        {
            if (grid[row][col].downWall.isPresent())
            {
                output << "---";
            }
            else
            {
                output << "   ";
            }
            output << "+";
        }
        output << std::endl;
    }
}

int Maze::getNumRows() const
{
    return numRows;
}

int Maze::getNumCols() const
{
    return numCols;
}

Cell &Maze::getCell(int row, int col)
{
    return grid[row][col];
}

bool Maze::isValidMove(int row, int col) const
{
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && !grid[row][col].isWall());
}

bool Maze::isValidMoveWall(int row, int col, int dir){
    Cell &cell = grid[row][col];
    switch (dir)
    {
    case 0:
        if (cell.downWall.isWall())
        {
            return false;
        }else{
            return true;
        }
    case 1:
        if (cell.rightWall.isWall())
        {
            return false;
        }else{
            return true;
        }
    case 2:
        if (cell.upWall.isWall())
        {
            return false;
        }else{
            return true;
        }
    case 3:
        if (cell.leftWall.isWall())
        {
            return false;
        }else{
            return true;
        }

    }
    return false;
}

bool Maze::isValidDirection(int row, int col, int Newrow, int Newcol){
    if (row == Newrow && col == Newcol-1)           //right (leftWall)
    {
        return isValidMoveWall(Newrow, Newcol, 3);
    }
    
    if (row == Newrow && col == Newcol+1)           //left  (rightWall)
    {
        return isValidMoveWall(Newrow, Newcol, 1);
    }
    
    if (row == Newrow-1 && col == Newcol)           //down(upWall)
    {
        return isValidMoveWall(Newrow, Newcol,2);
    }
    
    if (row == Newrow+1 && col == Newcol)           //up(downWall)
    {
        return isValidMoveWall(Newrow, Newcol,0);
    }
    return false;
}



void Maze::updateUserlocation(int userX, int userY){
    userRow = userX;
    userCol = userY;
}


string Maze::getName(){
    return mazeName;
}

Maze::Maze(const Maze &other)
{
    numRows = other.numRows;
    numCols = other.numCols;
    mazeName = other.mazeName; // Copy the maze name

    // Allocate memory for the new grid
    grid = new Cell *[numRows];
    for (int i = 0; i < numRows; ++i)
    {
        grid[i] = new Cell[numCols];
    }
    // Copy the contents of the other maze's grid
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            grid[i][j] = other.grid[i][j]; // Assuming Cell has proper copy constructor
        }
    }
}



namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        size_t operator()(const std::pair<int, int> &p) const
        {
            // Combine the hash of the two integers
            size_t hash1 = std::hash<int>{}(p.first);
            size_t hash2 = std::hash<int>{}(p.second);

            // Simple hash combining function
            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };
}


void Maze::resetCells()
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            grid[row][col].clearVisited();
            grid[row][col].setPath(false);
        }
    }
}

bool Maze::breadthFirstSearch(int startRow, int startCol, int exitRow, int exitCol)
{
    resetCells();
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(startRow, startCol));
    grid[startRow][startCol].markVisited();

    // Initialize the path array
    path.assign(numRows, std::vector<std::pair<int, int>>(numCols, std::make_pair(-1, -1)));

    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (row == exitRow && col == exitCol)
        {
            // Found the exit, reconstruct the path
            while (row != startRow || col != startCol)
            {
                grid[row][col].setPath(true);
                int prevRow = path[row][col].first;
                int prevCol = path[row][col].second;
                row = prevRow;
                col = prevCol;
            }
            return true;
        }

        // Check adjacent cells
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i)
        {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (isValidMove(newRow, newCol) && !grid[newRow][newCol].isVisited() && isValidDirection(row, col, newRow, newCol))
            {
                q.push(std::make_pair(newRow, newCol));
                grid[newRow][newCol].markVisited();
                path[newRow][newCol] = std::make_pair(row, col); // Store the previous cell's position
            }
        }
    }

    return false; // No path found
}

int calculateHeuristic(int row, int col, int exitRow, int exitCol)
{
    // Manhattan distance heuristic
    return std::abs(exitRow - row) + std::abs(exitCol - col);
}


bool Maze::astarSearch(int startRow, int startCol, int exitRow, int exitCol)
{
    resetCells();
    std::priority_queue<std::pair<int, std::pair<int, int>>> pq; // Priority queue based on fScore
    pq.push({0, {startRow, startCol}});
    grid[startRow][startCol].markVisited();

    // Initialize the path array
    path.assign(numRows, std::vector<std::pair<int, int>>(numCols, std::make_pair(-1, -1)));

    while (!pq.empty())
    {
        int row = pq.top().second.first;
        int col = pq.top().second.second;
        pq.pop();

        if (row == exitRow && col == exitCol)
        {
            // Found the exit, reconstruct the path
            while (row != startRow || col != startCol)
            {
                grid[row][col].setPath(true);
                int prevRow = path[row][col].first;
                int prevCol = path[row][col].second;
                row = prevRow;
                col = prevCol;
            }
            return true;
        }

        // Check adjacent cells
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i)
        {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];
            if (isValidMove(newRow, newCol) && !grid[newRow][newCol].isVisited() && isValidDirection(row, col, newRow,newCol))
            {
                int tentativeGScore = grid[row][col].getGScore() + 1;
                int heuristic = calculateHeuristic(newRow, newCol, exitRow, exitCol);
                int fScore = tentativeGScore + heuristic;

                pq.push({-fScore, {newRow, newCol}});
                grid[newRow][newCol].markVisited();
                // cout << "move to" << newRow << newCol << endl;
                path[newRow][newCol] = std::make_pair(row, col); // Store the previous cell's position
            }
        }
    }

    return false; // No path found
}

void Maze::printMazeWithPath() const
{
    // Print top border
    std::cout << " ";
    for (int col = 0; col < numCols; ++col)
    {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;

    for (int row = 0; row < numRows; ++row)
    {
        // Print cell contents and vertical walls
        for (int col = 0; col < numCols; ++col)
        {
            if (col == 0)
            {
                std::cout << "|";
            }

            if (row == userRow && col == userCol)
            {
                std::cout << " $ "; // Display the user character at their position
            }
            else if (row == 0 && col == 0)
            {
                std::cout << " E ";
            }
            else if (row == numRows - 1 && col == numCols - 1)
            {
                std::cout << " X ";
            }
            else if (path[row][col] != std::make_pair(-1, -1)) // Check if the cell is part of the path
            {
                std::cout << " * "; // Display the path marker
            }
            // else if (grid[row][col].isPath())
            // {                       // Check if the cell is part of the path
            //     std::cout << " * "; // Display the path marker
            // }
            else
            {
                std::cout << "   ";
            }

            if (grid[row][col].rightWall.isPresent())
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;

        // Print horizontal walls
        std::cout << "+";
        for (int col = 0; col < numCols; ++col)
        {
            if (grid[row][col].downWall.isPresent())
            {
                std::cout << "---";
            }
            else
            {
                std::cout << "   ";
            }
            std::cout << "+";
        }
        std::cout << std::endl;
    }
}

void Maze::resetPath()
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            path[row][col] = std::make_pair(-1, -1);
        }
    }
}

bool Maze::hasPath() const
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (path[row][col] != std::make_pair(-1, -1))
            {
                return true; // Path found in at least one cell
            }
        }
    }
    return false; // No path found in any cell
}

void Maze::startGame()
{
    User user(0, 0);

    // Print initial maze
    printMaze();
    bool success = false;

    while (!success)
    {
        // Get user input
        char input = getch();

        // Handle user input
        switch (input)
        {
        case 'w':
            if (isValidMove(user.getRow() - 1, user.getCol()))
            {
                if (isValidMoveWall(user.getRow() - 1, user.getCol(), 0))
                {
                    user.moveUp();
                    updateUserlocation(user.getRow(), user.getCol());
                }
            }
            break;
        case 'a':
            if (isValidMove(user.getRow(), user.getCol() - 1))
            {
                if (isValidMoveWall(user.getRow(), user.getCol() - 1, 1))
                {
                    user.moveLeft();
                    updateUserlocation(user.getRow(), user.getCol());
                }
            }
            break;
        case 's':
            if (isValidMove(user.getRow() + 1, user.getCol()))
            {
                if (isValidMoveWall(user.getRow() + 1, user.getCol(), 2))
                {
                    user.moveDown();
                    updateUserlocation(user.getRow(), user.getCol());
                }
            }
            break;
        case 'd':
            if (isValidMove(user.getRow(), user.getCol() + 1))
            {
                if (isValidMoveWall(user.getRow(), user.getCol() + 1, 3))
                {
                    user.moveRight();
                    updateUserlocation(user.getRow(), user.getCol());
                }
            }
            break;
        default:
            break;
        }

        // Check if user reached the exit
        if (user.getRow() == getNumRows() - 1 && user.getCol() == getNumCols() - 1)
        {
            success = true;
        }

        system("clear"); // Use system("cls") on Windows
        printMaze();
        cout << "\tUp - 'W'\nLeft - 'A'\tRight - 'D'\n\tDown - 'S'" << endl;
    }

    std::cout << "Congratulations! You reached the exit." << std::endl;
}

void Maze::setWall(int row, int col, bool hasWall)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        grid[row][col].setRightWall(hasWall);
        grid[row][col].setDownWall (hasWall);
    }
}


bool Maze::hasRightWall(int row, int col) const
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return grid[row][col].getRightWall();
    }
    return true; // Assuming out-of-bounds cells have walls
}

bool Maze::hasDownWall(int row, int col) const
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return grid[row][col].getDownWall();
    }
    return true; // Assuming out-of-bounds cells have walls
}

std::string Maze::compress() 
{ 
    std::ostringstream oss;

    // Maze name, number of rows, number of columns
    oss << getName() << " " << getNumRows() << " " << getNumCols() << " ";

    // Maze data
    for (int row = 0; row < getNumRows(); ++row)
    {
        for (int col = 0; col < getNumCols(); ++col)
        {
            if (grid[row][col].rightWall.isPresent())
            {
                oss << "1";
            }
            else
            {
                oss << "0";
            }
        }
    }

    return oss.str();
}