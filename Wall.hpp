// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

class Wall
{
public:
    Wall();
    void remove();
    bool isPresent() const;
    bool isWall() const; // Mark isWall() as const
    Wall(const Wall &other);
private:
    bool present;
};
