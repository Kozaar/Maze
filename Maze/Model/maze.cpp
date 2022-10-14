#include "maze.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Maze::Maze() {
    createMatrix(6, 6);
}

Maze::Maze(int rows, int cols) {
    createMatrix(rows, cols);
}

Maze::~Maze() {
    deleteMatrix();
}

void Maze::createMatrix(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new int*[rows_]();
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new int[cols_]();
    }
}

void Maze::generate(int rows, int cols) {
    recreateMatrix(rows, cols);
    if (rows_ > 1 && cols_ > 1) {
        generateFirstRow();
        generateMiddleRows();
        generateLastRow();
    } else {
        for (int i = 0; i < rows_; i++) {
            vectorForPrint.push_back(std::vector<std::pair<bool, bool> >(cols));
            vectorForPrint.at(i).at(cols-1).first = 1;
        }
        for (int i = 0; i < cols; i++) {
            vectorForPrint.at(rows-1).at(i).second = 1;
        }
    }
}

bool Maze::findSolution2(int xStart, int yStart, int xFinish, int yFinish) {
    bool isSolutionFind = false;
    solution.clear();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = 0;
        }
    }
    std::pair<int, int> finder(yStart, xStart);
    std::pair<bool, bool> direction(0, 0);
            /* 00 down
             * 01 left
             * 11 up
             * 10 right */
    int count = 0;
    int maxCount = 1000000;
    while (!(finder.second == xFinish && finder.first == yFinish) && count < maxCount) {
        while (!checkMovingRight(finder, direction) && count < maxCount) {
            if (finder.second == xFinish && finder.first == yFinish) {
                break;
            }
            if (checkMovingStraight(finder, direction)) {
                moveStraight(&finder, direction);
            } else {
                turnLeft(&direction);
            }
            count++;
        }
        if (finder.second == xFinish && finder.first == yFinish) {
            break;
        }
        if (checkMovingRight(finder, direction)) {
            turnRight(&direction);
            if (checkMovingStraight(finder, direction)) {
                moveStraight(&finder, direction);
            }
        }
        count++;
    }
    if (count < maxCount) {
        isSolutionFind = true;
    }
    solution.push_back({finder.second, finder.first});
    matrix_[finder.first][finder.second]++;
    return isSolutionFind;
}

std::vector<std::vector<std::pair<bool, bool> > > *Maze::getMaze() {
    return &vectorForPrint;
}

std::vector<std::pair<int, int> > *Maze::getSolutionMaze() {
    return &solution;
}

bool Maze::openFile(std::string fileName) {
    bool res = false;
    std::vector<std::vector<std::pair<bool, bool> > > fileData;
    res = MazeFile::getMazeDataFromFile(fileName, &fileData);
    if (res) {
        recreateMatrix(fileData.size(), fileData.at(0).size());
        vectorForPrint = fileData;
    }
    return res;
}

void Maze::saveInFile(std::string fileName) {
    MazeFile::setMazeInFile(fileName, vectorForPrint);
}

std::pair<int, int> Maze::getSize() {
    return std::pair<int, int>(rows_, cols_);
}

bool Maze::findSolution(int xStart, int yStart, int xFinish, int yFinish) {
    std::vector<std::vector<std::pair<bool, bool> > > copyVectorForPrint;
    for (size_t i = 0; i < vectorForPrint.size(); i++) {
        copyVectorForPrint.push_back(vectorForPrint.at(i));
    }
    findSolution2(xStart, yStart, xFinish, yFinish);
    bool isSolutionFind = findSolution2(xStart, yStart, xFinish, yFinish);
    swap(vectorForPrint, copyVectorForPrint);
    return isSolutionFind;
}

void Maze::recreateMatrix(int rows, int cols) {
    if (rows_ != rows || cols_ != cols) {
        deleteMatrix();
        createMatrix(rows, cols);
    }
    for (size_t i = 0; i < vectorForPrint.size(); i++) {
        vectorForPrint.at(i).clear();
    }
    vectorForPrint.clear();
}

void Maze::deleteMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        rows_ = cols_ = 0;
        matrix_ = nullptr;
    }
    for (size_t i = 0; i < vectorForPrint.size(); i++) {
        vectorForPrint.at(i).clear();
    }
    vectorForPrint.clear();
    solution.clear();
}

void Maze::generateFirstRow() {
    for (int i = 0; i < cols_; i++) {
        matrix_[0][i] = i + 1;
    }
    vectorForPrint.push_back(std::vector<std::pair<bool, bool> >(cols_));
    makeRightWall(0);
    makeDownWall(0);
}

void Maze::generateMiddleRows() {
    int maxVar = 0;
    for (int i = 1; i < rows_-1; i++) {
        maxVar = 0;
        vectorForPrint.push_back(vectorForPrint.at(i-1));
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i-1][j];
            if (matrix_[i][j] > maxVar) maxVar = matrix_[i][j];
            vectorForPrint.at(i).at(j).first = 0;
            if (vectorForPrint.at(i).at(j).second) {
                matrix_[i][j] = 0;
                vectorForPrint.at(i).at(j).second = 0;
            }
        }
        maxVar++;
        for (int j = 0; j < cols_; j++) {
            if (matrix_[i][j] == 0) {
                matrix_[i][j] = maxVar;
                maxVar++;
            }
        }
        makeRightWall(i);
        makeDownWall(i);
    }
}

void Maze::generateLastRow() {
    vectorForPrint.push_back(vectorForPrint.at(rows_ - 2));
    int maxVar = 0;
    for (int j = 0; j < cols_; j++) {
        matrix_[rows_ - 1][j] = matrix_[rows_ - 2][j];
        if (matrix_[rows_ - 1][j] > maxVar) maxVar = matrix_[rows_ - 1][j];
        if (vectorForPrint.at(rows_ - 1).at(j).second) {
            matrix_[rows_ - 1][j] = 0;
        }
        vectorForPrint.at(rows_ - 1).at(j).second = 1;
    }
    maxVar++;
    for (int j = 0; j < cols_; j++) {
        if (matrix_[rows_ - 1][j] == 0) {
            matrix_[rows_ - 1][j] = maxVar;
            maxVar++;
        }
    }
    makeRightWall(rows_-1);
    for (int i = 0; i < cols_ - 1; i++) {
        if (matrix_[rows_ - 1][i] != matrix_[rows_ - 1][i+1]) {
            vectorForPrint.at(rows_-1).at(i).first = 0;
            mergeVar(matrix_[rows_ - 1][i], matrix_[rows_ - 1][i+1]);
        }
    }
}

void Maze::makeRightWall(int row) {
    for (int i = 0; i < cols_-1; i++) {
        if (arc4random_uniform(2) || matrix_[row][i] == matrix_[row][i+1]) {
            vectorForPrint.at(row).at(i).first = 1;
        } else {
            vectorForPrint.at(row).at(i).first = 0;
            mergeVar(matrix_[row][i], matrix_[row][i+1]);
        }
    }
    vectorForPrint.at(row).at(cols_-1).first = 1;
}

void Maze::makeDownWall(int row) {
    bool exitExist = false;
    for (int i = 0; i < cols_-1; i++) {
        if (!exitExist && matrix_[row][i] != matrix_[row][i+1]) {
            vectorForPrint.at(row).at(i).second = 0;
        } else if (arc4random_uniform(2)) {
            vectorForPrint.at(row).at(i).second = 1;
        } else {
            vectorForPrint.at(row).at(i).second = 0;
            exitExist = true;
        }
        if (matrix_[row][i] != matrix_[row][i+1]) {
            exitExist = false;
        }
    }
    if (!exitExist) {
        vectorForPrint.at(row).at(cols_-1).second = 0;
    } else {
        vectorForPrint.at(row).at(cols_-1).second = arc4random_uniform(2);
    }
}

void Maze::mergeVar(int first, int second) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (matrix_[i][j] == second) {
                matrix_[i][j] = first;
            }
        }
    }
}

bool Maze::checkMovingRight(const std::pair<int, int> &finder, const std::pair<bool, bool> &direction) {
    /* 00 down
     * 01 left
     * 11 up
     * 10 right */
    bool ability = false;
    if (direction == std::pair<bool, bool>(0, 0)) {
        if (finder.second > 0 && !vectorForPrint.at(finder.first).at(finder.second-1).first) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(0, 1)) {
        if (finder.first > 0 && !vectorForPrint.at(finder.first-1).at(finder.second).second) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 1)) {
        if (finder.second < cols_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).first) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 0)) {
        if (finder.first < rows_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).second) {
            ability = true;
        }
    }
    return ability;
}

void Maze::turnRight(std::pair<bool, bool> *direction) {
    if (*direction == std::pair<bool, bool>(0, 0)) {
        direction->second = 1;
    } else if (*direction == std::pair<bool, bool>(0, 1)) {
        direction->first = 1;
    } else if (*direction == std::pair<bool, bool>(1, 1)) {
        direction->second = 0;
    } else if (*direction == std::pair<bool, bool>(1, 0)) {
        direction->first = 0;
    }
}

bool Maze::checkMovingLeft(const std::pair<int, int> &finder, const std::pair<bool, bool> &direction) {
    /* 00 down
     * 01 left
     * 11 up
     * 10 right */
    bool ability = false;
    if (direction == std::pair<bool, bool>(0, 0)) {
        if (finder.second > 0 && !vectorForPrint.at(finder.first).at(finder.second-1).first) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(0, 1)) {
        if (finder.first > 0 && !vectorForPrint.at(finder.first-1).at(finder.second).second) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 1)) {
        if (finder.second < cols_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).first) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 0)) {
        if (finder.first < rows_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).second) {
            ability = true;
        }
    }
    return ability;
}

void Maze::turnLeft(std::pair<bool, bool> *direction) {
    if (*direction == std::pair<bool, bool>(0, 0)) {
        direction->first = 1;
    } else if (*direction == std::pair<bool, bool>(0, 1)) {
        direction->second = 0;
    } else if (*direction == std::pair<bool, bool>(1, 1)) {
        direction->first = 0;
    } else if (*direction == std::pair<bool, bool>(1, 0)) {
        direction->second = 1;
    }
}

bool Maze::checkMovingStraight(const std::pair<int, int> &finder, const std::pair<bool, bool> &direction) {
    bool ability = false;
    if (direction == std::pair<bool, bool>(0, 0)) {
        if (finder.first < rows_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).second) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(0, 1)) {
        if (finder.second > 0 && !vectorForPrint.at(finder.first).at(finder.second-1).first) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 1)) {
        if (finder.first > 0 && !vectorForPrint.at(finder.first-1).at(finder.second).second) {
            ability = true;
        }
    } else if (direction == std::pair<bool, bool>(1, 0)) {
        if (finder.second < cols_ - 1 && !vectorForPrint.at(finder.first).at(finder.second).first) {
            ability = true;
        }
    }
    return ability;
}

void Maze::moveStraight(std::pair<int, int> *finder, const std::pair<bool, bool> &direction) {
    solution.push_back({finder->second, finder->first});
    matrix_[finder->first][finder->second]++;
    if (direction == std::pair<bool, bool>(0, 0)) {
            finder->first++;
            if (matrix_[finder->first][finder->second] != 0) {
                vectorForPrint.at(finder->first-1).at(finder->second).second = 1;
        }
    } else if (direction == std::pair<bool, bool>(0, 1)) {
            finder->second--;
            if (matrix_[finder->first][finder->second] != 0) {
                vectorForPrint.at(finder->first).at(finder->second).first = 1;
        }
    } else if (direction == std::pair<bool, bool>(1, 1)) {
            finder->first--;
            if (matrix_[finder->first][finder->second] != 0) {
                vectorForPrint.at(finder->first).at(finder->second).second = 1;
        }
    } else if (direction == std::pair<bool, bool>(1, 0)) {
            finder->second++;
            if (matrix_[finder->first][finder->second] != 0) {
                vectorForPrint.at(finder->first).at(finder->second-1).first = 1;
            }
    }
}
