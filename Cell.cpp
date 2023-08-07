// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cell.hpp"


Cell::Cell() : visited(false) {}

bool Cell::isVisited() const
{
    return visited;
}

void Cell::markVisited()
{
    visited = true;
}

bool Cell::isPath() const
{
    return !visited && !isWall(); // Return true if the cell is not visited and not a wall
}

void Cell::clearVisited()
{
    visited = false;
}


bool Cell::isWall() const {
    return upWall.isWall() && downWall.isWall() && leftWall.isWall() && rightWall.isWall();
}

// Cell copy constructor
Cell::Cell(const Cell &other)
{
    visited = other.visited;
    upWall = Wall(other.upWall);       // Call Wall copy constructor for upWall
    downWall = Wall(other.downWall);   // Call Wall copy constructor for downWall
    leftWall = Wall(other.leftWall);   // Call Wall copy constructor for leftWall
    rightWall = Wall(other.rightWall); // Call Wall copy constructor for rightWall
}

void Cell::setPath(bool isPath)
{
    path = isPath;
}

bool Cell::isWallCell(){
    return upWall.isWall() || downWall.isWall() ||leftWall.isWall() || rightWall.isWall();
}

bool Cell::setRightWall(bool wl){
    hasRightWall = wl;
    return true;
}
bool Cell::setDownWall(bool wl){
    hasDownWall = wl;
    return true;
}
