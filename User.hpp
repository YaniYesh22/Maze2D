// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>

class User
{
public:
    User(int startRow, int startCol) : row(startRow), col(startCol) {}

    int getRow() const { return row; }
    int getCol() const { return col; }

    void move(int newRow, int newCol)
    {
        row = newRow;
        col = newCol;
    }
    int getX() const
    {
        return col;
    }

    int getY() const
    {
        return row;
    }

    void moveUp()
    {
        row -= 1;
    }

    void moveLeft()
    {
        col -= 1;
    }

    void moveDown()
    {
        row += 1;
    }

    void moveRight()
    {
        col += 1;
    }

private:
    int row;
    int col;
};
