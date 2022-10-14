#ifndef SRC_MAZE_MODEL_MAZE_H_
#define SRC_MAZE_MODEL_MAZE_H_

#include <vector>
#include <string>
#include "mazefile.h"


class Maze {
 public:
    Maze();
    Maze(int rows, int cols);
    ~Maze();
    void generate(int rows, int cols);
    bool findSolution(int xStart, int yStart, int xFinish, int yFinish);
    std::vector<std::vector<std::pair<bool, bool> > >* getMaze();
    std::vector<std::pair<int, int> >* getSolutionMaze();
    bool openFile(std::string fileName);
    void saveInFile(std::string fileName);
    std::pair<int, int> getSize();

 private:
    int cols_;
    int rows_;
    int** matrix_;

    std::vector<std::vector<std::pair<bool, bool> > > vectorForPrint;
    std::vector<std::pair<int, int> > solution;

    void createMatrix(int rows, int cols);
    void recreateMatrix(int rows, int cols);
    void deleteMatrix();
    void generateFirstRow();
    void generateMiddleRows();
    void generateLastRow();
    void makeRightWall(int row);
    void makeDownWall(int row);
    void mergeVar(int first, int second);
    bool checkMovingRight(const std::pair<int, int>& finder, const std::pair<bool, bool>& direction);
    void turnRight(std::pair<bool, bool> *direction);
    bool checkMovingLeft(const std::pair<int, int>& finder, const std::pair<bool, bool>& direction);
    void turnLeft(std::pair<bool, bool> *direction);
    bool checkMovingStraight(const std::pair<int, int>& finder, const std::pair<bool, bool>& direction);
    void moveStraight(std::pair<int, int>* finder, const std::pair<bool, bool>& direction);
    bool findSolution2(int xStart, int yStart, int xFinish, int yFinish);
};

#endif  // SRC_MAZE_MODEL_MAZE_H_
