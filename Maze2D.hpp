////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <list>
#include <map>
#include <stdio.h>
#include "Maze.hpp"
// #include <string.h>
void saveCompressedMazeToFile(const std::string &compressedMaze, const std::string &filename);

using namespace std;

class Maze2D
{
private:
    list<Maze> MazeList;
    std::map<std::string, std::pair<Maze *, vector<std::pair<int, int>>>> solutionDB;

public:
    Maze2D();
    ~Maze2D();
    Maze createMaze(string name, int width, int height);
    void playInMaze(string name);
    void showMaze(string name);
    size_t getSizeOfMaze(std::string &name) ;
    void solveMaze(string name,int algorithm);
    void saveMazeToFile(string& fileName);
    void saveCompresedMazes();
    void loadMazesFromFile(const std::string &filename);
};

