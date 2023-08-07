// Yanai Yeshurun – 318666146
// Omer Ben Israel – 315771394
// Nir Itah  - 207279316

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Maze2D.hpp"
#include "Maze.hpp"
#include "User.hpp"
#include "File.hpp"
#include <cstdlib> // For system()
#include <cstdio>  // For getchar()
#include <iostream>
#ifdef _WIN32
#include <conio.h> // For _getch() on Windows
#else
#include <termios.h>
#include <unistd.h>
#endif
// Cross-platform getch() function

void showFilesInPath(std::string);


int main()
{
    Maze2D Mazes;
    int selection = 0;
    for (;;)
    {
        cout << "\n\t\tMenu\n"
             << endl;
        cout << "1 - Show All Files In Path\t2 - Generate Maze\t3 - Display Maze By Name\t\n4 - Show Maze Size By Name\t5 - Solve Maze   \t6 - Play Maze By Name\n7 - Save All Mazes To File\t8 - Compress all mazes\t9 - Reload compressed Mazes"
             << endl;
        cin >> selection;
        while (!(selection >= 0 && selection <= 9))
        {
            cout << "Invalid selection -- Try again ( 1 - 9 )" << endl;
            cin >> selection;
        }
        switch (selection)
        {
        case 1:{
            std::string path;
            cout << "Enter File Path:" << endl;
            cin >> path;
            showFilesAndDirectoriesInPath(path);
            break;
        }
        case 2:
        {
            std::string mazeName;
            cout << "Enter Maze Name:" << endl;
            cin >> mazeName;
            int rows , cols;
            cout << "Enter Maze Width:" << endl;
            cin >> rows;
            cout << "Enter Maze Height:" << endl;
            cin >> cols;
            Mazes.createMaze(mazeName, cols, rows);
            break;
        }
        case 3:
        {
            std::string mazeName;
            cout << "Enter Maze Name:" << endl;
            cin >> mazeName;
            Mazes.showMaze(mazeName);
            break;
        }
        case 4:
        {
            std::string mazeName;
            cout << "Enter Maze Name:" << endl;
            cin >> mazeName;
            cout << "The " << mazeName << "Maze Is " << Mazes.getSizeOfMaze(mazeName) << " B"<<endl;
            break;
        }
        case 5:
        {
            std::string mazeName;
            int algo = 0;
            cout << "Enter Maze Name:" << endl;
            cin >> mazeName;
            cout << "Enter Algorithm:\n1)BFS\n2)AStar\n" << endl;
            cin >> algo;
            while (algo <1 || algo > 2)
            {
                cout << "Invalid Choice Try Again" <<endl;
                cin >> algo;
            }
            Mazes.solveMaze(mazeName, algo);
            break;
        }
        case 6:{
            std::string mazeName;
            cout << "Enter Maze Name:" << endl;
            cin >> mazeName;
            Mazes.playInMaze(mazeName);
        }
        break;

        case 7:{
            std::string fileName;
            cout << "Enter File Name:" << endl;
            cin >> fileName;
            Mazes.saveMazeToFile(fileName);
        }
        break;

        case 8:{
            Mazes.saveCompresedMazes();
        }
        break;

        case 9:{
            std::string fileName;
            cout << "Enter File Name:" << endl;
            cin >> fileName;
            Mazes.loadMazesFromFile(fileName);
        }
        break;

        default:
            break;
        }
    }
    return 0;
}
