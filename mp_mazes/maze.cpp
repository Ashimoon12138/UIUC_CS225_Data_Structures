#include "maze.h"

void SquareMaze::makeMaze(int width, int height) {
    if (width < 0 || height < 0) {
        cerr << "Invalid input!" << endl;
        cerr << "the width and the height should always be positive integer." << endl;
        return;
    }
    this->mainMaze = DisjointSets();

    this->_width = width;
    this->_height = height;
    this->mainMaze.addelements(width * height);
    this->rightWall = vector<bool>();
    this->downWall = vector<bool>();
    for (size_t i = 0; i < (size_t) width * height; i++){
        rightWall.push_back(true); downWall.push_back(true);
    }

    const size_t MAX_WIDTH_INDEX = width - 1;
    const size_t MAX_HEIGHT_INDEX = height - 1;

    size_t wallBreakCount = 0;

    while (wallBreakCount < _width * _height - 1) {
        if (randomBool()) {
            size_t x = std::rand() % this->_width;
            size_t y = std::rand() % this->_height;
            size_t thisIndex = y * this->_width + x;
            size_t rightIndex = thisIndex + 1;
            size_t downIndex = thisIndex + this->_width;

            bool breakRight = x < MAX_WIDTH_INDEX && mainMaze.find(thisIndex) != mainMaze.find(rightIndex);
            bool breakDown = y < MAX_HEIGHT_INDEX && mainMaze.find(thisIndex) != mainMaze.find(downIndex);

            if (breakRight) {
                setWall(x, y, Direction::right, false);
                mainMaze.setunion(mainMaze.find(thisIndex), mainMaze.find(rightIndex));
                wallBreakCount++;
            } else if (breakDown) {
                setWall(x, y, Direction::down, false);
                mainMaze.setunion(mainMaze.find(thisIndex), mainMaze.find(downIndex));
                wallBreakCount++;
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    size_t thisIndex = y * _width + x;

    switch (dir) {
        case Direction::right:
            if (x + 1 == (int) _width) { return false; }
            return !rightWall[thisIndex];
        case Direction::down:
            if (y + 1 == (int) _height) { return false; }
            return !downWall[thisIndex];
        case Direction::left:
            if (x == 0) { return false; }
            return !rightWall[thisIndex - 1];
        case Direction::up:
            if (y == 0) { return false; }
            return !downWall[thisIndex - _width];
        default:
            cerr << "Wrong input of dir!" << endl;
            cerr << "Dir should be integers within 0 to 3." << endl;
            return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    size_t thisIndex = y * _width + x;

    switch (dir) {
        case Direction::right:
            if (x + 1 == (int) _width) { return; }
            rightWall[thisIndex] = exists ? true : false;
            return;
        case Direction::down:
            if (y + 1 == (int) _height) { return; }
            downWall[thisIndex] = exists ? true : false;
            return;
        default:
            cerr << "Wrong input of dir!" << endl;
            cerr << "dir should be 0 or 1." << endl;
            return;
    }
}

vector<int> SquareMaze::solveMaze() const {
    size_t x = 0;
    size_t y = 0;
    size_t currIndex = y * _width + x;

    vector<size_t> visited;
    for (size_t i = 0; i < this->_width * this->_height; i++) {
        visited.push_back(false);
    }

    map<size_t, size_t> preCell;
    map<size_t, unsigned int> distanceMap;
    distanceMap[currIndex] = 0;

    queue<size_t> q;
    q.push(currIndex);

    while (!q.empty()) {
        currIndex = q.front();
        q.pop();
        visited[currIndex] = true;
        x = currIndex % _width;
        y = (currIndex - x) / _width;

        size_t rightIndex = currIndex + 1;
        size_t downIndex = currIndex + _width;
        size_t leftIndex = currIndex - 1;
        size_t upIndex = currIndex - _width;

        bool travelRight = canTravel(x, y, Direction::right) && !visited[rightIndex];
        bool travelDown = canTravel(x, y, Direction::down) && !visited[downIndex];
        bool travelLeft = canTravel(x, y, Direction::left) && !visited[leftIndex];
        bool travelUp = canTravel(x, y, Direction::up) && !visited[upIndex];

        if (travelRight) {
            q.push(rightIndex);
            preCell[rightIndex] = currIndex;
            distanceMap[rightIndex] = distanceMap[currIndex] + 1;
            visited[rightIndex] = true;
        }
        if (travelDown) {
            q.push(downIndex);
            preCell[downIndex] = currIndex;
            distanceMap[downIndex] = distanceMap[currIndex] + 1;
            visited[downIndex] = true;
        }
        if (travelLeft) {
            q.push(leftIndex);
            preCell[leftIndex] = currIndex;
            distanceMap[leftIndex] = distanceMap[currIndex] + 1;
            visited[leftIndex] = true;
        }
        if (travelUp) {
            q.push(upIndex);
            preCell[upIndex] = currIndex;
            distanceMap[upIndex] = distanceMap[currIndex] + 1;
            visited[upIndex] = true;
        }
    }

    size_t maxDistance = 0;
    size_t maxIndex = 0;

    for (size_t bottomIndex = (_height - 1) * _width; bottomIndex < _height * _width; bottomIndex++) {
        size_t currDistance = distanceMap[bottomIndex];
        if (currDistance > maxDistance) {
            maxDistance = currDistance;
            maxIndex = bottomIndex;
        }
    }

    size_t backIndex = maxIndex;

    vector<int> path;
    while (backIndex != 0) {
        size_t preIndex = preCell[backIndex];

        if (backIndex - preIndex == 1) { // current is the parents right
            path.insert(path.begin(), Direction::right);
            backIndex = preIndex;
        } else if (preIndex - backIndex == 1) {
            path.insert(path.begin(), Direction::left);
            backIndex = preIndex;
        } else if (preIndex - backIndex == _width) {
            path.insert(path.begin(), Direction::up);
            backIndex = preIndex;
        } else if (backIndex - preIndex == _width) {
            path.insert(path.begin(), Direction::down);
            backIndex = preIndex;
        }
    }
    return path;
}


PNG* SquareMaze::drawMaze() const {
    PNG *theMazePNG = new PNG(_width * 10 + 1, _height * 10 + 1);
    /* Blacken the top most pixels, except for column 1 to 9 */
    for (size_t i = 0; i < _width * 10 + 1; i++) {
        if (i < 1 || i > 9) {
            HSLAPixel & pixel = theMazePNG->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    /* Blacken the left most pixels*/
    for (size_t i = 1; i < _height * 10 + 1; i++) {
        HSLAPixel & pixel = theMazePNG->getPixel(0, i);
        pixel.l = 0;
    }
    /* Find out all the walls and paint them on the PNG */
    for (size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _height; y++) {
            size_t i = y * _width + x;
            if (rightWall[i]) {
                for (size_t k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = theMazePNG->getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;
                }
            }
            if (downWall[i]) {
                for (size_t k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;
                }
            }
        }
    }
    return theMazePNG;
}

PNG* SquareMaze::drawMazeWithSolution() const {
    PNG* theMazePNG = drawMaze();
    vector<int> theSolution = solveMaze();

    size_t x = 5;
    size_t y = 5;
    size_t xCell = 0;
    size_t yCell = 0;
    HSLAPixel redPixel(0, 1, 0.5, 1);

    for (int & i : theSolution) {
        switch (i) {
            case Direction::right:
                for (int i = 0; i <= 10 ; i++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x + i, y);
                    pixel = redPixel;
                }
                x += 10;
                xCell++;
                break;
            case Direction::down:
                for (int i = 0; i <= 10 ; i++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x, y + i);
                    pixel = redPixel;
                }
                y += 10;
                yCell++;
                break;
            case Direction::left:
                for (int i = 0; i <= 10 ; i++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x - i, y);
                    pixel = redPixel;
                }
                x -= 10;
                xCell--;
                break;
            case Direction::up:
                for (int i = 0; i <= 10 ; i++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x, y - i);
                    pixel = redPixel;
                }
                y -= 10;
                yCell--;
                break;
            default:
                break;
        }
    }

    for (size_t k = 1; k <= 9; k++) {
      HSLAPixel & pixel = theMazePNG->getPixel(xCell * 10 + k, (yCell + 1) * 10);
      pixel.l = 1;
    }

    return theMazePNG;
}
//
//
// void SquareMaze::makeCreativeMaze(int width, int height) {
//     if (width < 0 || height < 0) {
//         cerr << "Invalid input!" << endl;
//         cerr << "the width and the height should always be positive integer." << endl;
//         return;
//     }
//     this->mainMaze = DisjointSets();
//
//     this->_width = width;
//     this->_height = height;
//     this->mainMaze.addelements(width * height);
//     this->rightWall = vector<bool>();
//     this->downWall = vector<bool>();
//     for (size_t i = 0; i < (size_t) (width * height); i++){
//         rightWall.push_back(true); downWall.push_back(true);
//     }
//
//     const size_t MAX_WIDTH_INDEX = width - 1;
//     const size_t MAX_HEIGHT_INDEX = height - 1;
//
//     size_t wallBreakCount = 0;
//     while (wallBreakCount < (size_t) ((3 * width * height) / 4) - 1) {
//         if (randomBool()) {
//             size_t x = std::rand() % this->_width;
//             size_t y = std::rand() % this->_height;
//             size_t thisIndex = y * this->_width + x;
//             size_t rightIndex = thisIndex + 1;
//             size_t downIndex = thisIndex + this->_width;
//             vector<bool> volid;
//             for(size_t i = 0; i < (size_t) (_width * _height); i ++) {
//               volid.push_back(true);
//             }
//             for (size_t x = 0; x < _width; x++) {
//                 for (size_t y = 0; y < _height; y++) {
//                   if(x >= 0.5 * _width && y <= 0.5 * _height) {
//                     volid[thisIndex] = false;
//                   }
//                }
//             }
//
//
//             bool breakRight = x < MAX_WIDTH_INDEX && volid[thisIndex] && mainMaze.find(thisIndex) != mainMaze.find(rightIndex);
//             bool breakDown = y < MAX_HEIGHT_INDEX && volid[thisIndex] && mainMaze.find(thisIndex) != mainMaze.find(downIndex);
//
//             if (breakRight) {
//                 setWall(x, y, Direction::right, false);
//                 mainMaze.setunion(mainMaze.find(thisIndex), mainMaze.find(rightIndex));
//                 wallBreakCount++;
//             } else if (breakDown) {
//                 setWall(x, y, Direction::down, false);
//                 mainMaze.setunion(mainMaze.find(thisIndex), mainMaze.find(downIndex));
//                 wallBreakCount++;
//             }
//         }
//     }
//     // std::cout << "/* message222 */" << '\n';
// }

PNG* SquareMaze::drawCreativeMaze() const {
    PNG *theMazePNG = new PNG(_width * 10 + 1, _height * 10 + 1);
    /* Blacken the top most pixels, except for column 1 to 9 */
    for (size_t i = 0; i < _width * 5 + 1; i++) {
        if (i < 1 || i > 9) {
            HSLAPixel & pixel = theMazePNG->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    for (size_t i = _width * 5; i >= (_width * 5) && i < _width * 10 + 1; i++) {
            HSLAPixel & pixel = theMazePNG->getPixel(i, _height * 5 + 10);
            pixel.l = 0;
    }
    /* Blacken the left most pixels*/
    for (size_t i = 1; i < _height * 10 + 1; i++) {
        HSLAPixel & pixel = theMazePNG->getPixel(0, i);
        pixel.l = 0;
    }
    //Blacken the right
    for (size_t i = 0; i < _height * 5 + 1; i++) {
        HSLAPixel & pixel = theMazePNG->getPixel(_width * 5, i);
        pixel.l = 0;
    }
    /* Find out all the walls and paint them on the PNG */

    vector<bool> volid;
    for(size_t i = 0; i < (size_t) (_width * _height); i ++) {
      volid.push_back(true);
    }
    for (size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _height; y++) {
          size_t i = y * _width + x;
          if(x >= 0.5 * _width && y <= 0.5 * _height) {
            volid[i] = false;
          }
       }
    }

    for (size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _height; y++) {
            size_t i = y * _width + x;
            if (rightWall[i] && volid[i]) {
                for (size_t k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = theMazePNG->getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;
                }
            }
            if (downWall[i] && volid[i]) {
                for (size_t k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = theMazePNG->getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;
                }
            }
        }
    }
    return theMazePNG;
}
