#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

void printVec(vector<int> v) {
    for (auto const & elem : v) {
        cout << elem << "|";
    }
    cout << endl;
}

int main()
{
    // // Write your own main here
    SquareMaze maze;
    maze.makeMaze(100, 120);
    PNG* theMaze = maze.drawCreativeMaze();
    theMaze->writeToFile("myMaze.png");
    // // printVec(maze.solveMaze());
    // // delete theMaze;
    //
    // // Write your own main here
    // // SquareMaze maze;
    // // maze.drawCreativeMaze();
    // // PNG* theMazePNG = drawCreativeMaze();
    // // PNG* theMaze = maze.drawMazeWithSolution();
    // theMaze->writeToFile("myMaze.png");
    // // printVec(maze.solveMaze());
    delete theMaze;
    return 0;
}
