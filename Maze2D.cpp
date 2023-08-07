////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Maze2D.hpp"
#include "BFS.hpp"
#include "AStar.hpp"
#include "Maze.hpp"
#include <memory>
using namespace std;
Maze2D::Maze2D() {}
Maze2D::~Maze2D() {}

Maze Maze2D::createMaze(string name, int width, int height)
{
    MazeList.push_back(Maze(width, height, name)); // Add the maze to the list
    cout << name << " Created Succesfully" << endl;
    Maze &lastMaze = MazeList.back(); // Get a reference to the last maze in the list
    lastMaze.generateMaze();
    lastMaze.printMaze();
    return lastMaze;
}

void Maze2D::showMaze(string name)
{
    bool found = false;
    for (Maze &maze : MazeList)
    {
        if (maze.getName() == name)
        {
            found = true;
            // Perform actions to display the maze
            maze.printMaze(); // Replace with the actual display logic
            break;            // Stop searching since maze is found
        }
    }
    if (!found)
    {
        std::cout << "Maze with name '" << name << "' not found." << std::endl;
    }
}

size_t Maze2D::getSizeOfMaze(std::string &name)
{
    bool found = false;

    for (Maze &maze : MazeList)
    {
        if (maze.getName() == name)
        {
            found = true;

            // Calculate the size of the maze based on its data
            size_t mazeSize = sizeof(maze);
            mazeSize += maze.getNumRows() * maze.getNumCols() * sizeof(Cell);
            return mazeSize;
        }
    }
    if (!found)
    {
        std::cout << "Maze with name '" << name << "' not found." << std::endl;
    }
    return 0; // Return 0 if maze not found
}

void Maze2D::solveMaze(string name, int algorithm)
{

    bool found = false;
    for (Maze &maze : MazeList)
    {
        if (maze.getName() == name)
        {
            found = true;
            Maze &lastMaze = maze;
            if (algorithm >= 1 && algorithm <= 3)
            {
                switch (algorithm)
                {
                case 1:
                {
                    int startRow = 0;                    // Set the start row
                    int startCol = 0;                    // Set the start column
                    int exitRow = maze.getNumRows() - 1; // Set the exit row
                    int exitCol = maze.getNumCols() - 1; // Set the exit column

                    if (maze.breadthFirstSearch(startRow, startCol, exitRow, exitCol))
                    {
                        maze.printMazeWithPath();
                    }
                    else
                    {
                        std::cout << "No path found." << std::endl;
                    }
                }
                break;
                case 2:
                {
                    int startRow = 0;                    // Set the start row
                    int startCol = 0;                    // Set the start column
                    int exitRow = maze.getNumRows() - 1; // Set the exit row
                    int exitCol = maze.getNumCols() - 1; // Set the exit column
                    if (maze.astarSearch(startRow, startCol, exitRow, exitCol))
                    {
                        maze.printMazeWithPath();
                    }
                    else
                    {
                        std::cout << "No path found." << std::endl;
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
    }
    if (!found)
    {
        std::cout << "Maze with name '" << name << "' not found." << std::endl;
    }
}

void Maze2D::playInMaze(string name){
    bool found = false;

    for (Maze &maze : MazeList)
    {
        if (maze.getName() == name)
        {
            found = true;
            maze.startGame();
        }
    }
    if (!found)
    {
        std::cout << "Maze with name '" << name << "' not found." << std::endl;
    }
    return ; // Return 0 if maze not found
}


void Maze2D::saveMazeToFile(std::string &fileName)
{
    bool found = false;
    std::ofstream outFile(fileName);

    for (Maze &maze : MazeList)
    {
        found = true;
        if (outFile)
        {
            maze.printMaze(outFile);
        }
    }
    outFile.close();

    if (!found)
    {
        std::cout << "Mazes not found." << std::endl;

        // Remove the file if it exists
        if (std::remove(fileName.c_str()) != 0)
        {
            std::cerr << "Error deleting file: " << fileName << std::endl;
        }
    }
}


void Maze2D::saveCompresedMazes(){
    bool found = false;
    std::ostringstream allCompressedMazes;
    for (Maze &maze : MazeList)
    {
        found = true;
        std::string compressedMaze = maze.compress();
        allCompressedMazes << compressedMaze << "\n";
    }
    std::string filename = "all_compressed_mazes.txt";
    saveCompressedMazeToFile(allCompressedMazes.str(), filename);
    if (!found)
    {
        std::cout << "Mazes not found." << std::endl;
    }
}


void Maze2D::loadMazesFromFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string mazeLine;
    while (std::getline(inputFile, mazeLine))
    {
        std::istringstream iss(mazeLine);

        std::string mazeName;
        int numRows, numCols;
        iss >> mazeName >> numRows >> numCols;

        Maze maze(numRows, numCols, mazeName);

        std::string mazeData;
        iss >> mazeData;

        int index = 0;
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                if (mazeData[index] == '1')
                {
                    maze.setWall(row, col, true);
                }
                else
                {
                    maze.setWall(row, col, false);
                }
                ++index;
            }
        }

        maze.generateMaze();
        maze.printMaze(std::cout);
        MazeList.push_back(maze);
    }

    inputFile.close();
}

