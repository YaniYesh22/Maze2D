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
