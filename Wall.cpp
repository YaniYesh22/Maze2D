// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Wall.hpp"

Wall::Wall() : present(true) {}

void Wall::remove()
{
    present = false;
}

bool Wall::isPresent() const
{
    return present;
}

bool Wall::isWall() const
{
    return present; // isWall() is now marked as const
}

// Wall copy constructor
Wall::Wall(const Wall &other)
{
    present = other.present;
}