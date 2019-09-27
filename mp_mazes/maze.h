#pragma once

#include "dsets.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <vector>
using std::vector;

#include <algorithm>
#include <cstdlib>

#include <queue>
using std::queue;

#include <map>
using std::map;
using std::pair;

#include "cs225/PNG.h"
using namespace cs225;

class SquareMaze {
    public:
    SquareMaze() {};

    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);

    vector<int> solveMaze() const;
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution() const;
    PNG* drawCreativeMaze() const;
    // void makeCreativeMaze(int width, int height);

    private:
    /**
     * The maze, implemented as a DisjointSets.
     */
    DisjointSets mainMaze;
    /**
     * A vector to store the existence of the right wall on a cell.
     * true if the wall exist, false otherwise.
     */
    vector<bool> rightWall;
    /**
     * A vector to store the existence of the down wall on a cell.
     * true if the wall exist, false otherwise.
     */
    vector<bool> downWall;

    size_t _width;
    size_t _height;

    /**
     * A helper function to generate a randomised boolean value
     */
    bool randomBool() { return std::rand() % 2 == 0; }

    vector<int> _solveMaze(size_t x, size_t y, int toDirection) const ;
};
/**
 * An enum collection to store each direction's identificaiton number.
 */
enum Direction {right = 0, down = 1, left = 2, up = 3};
