#ifndef SRC_MAZE_MODEL_CAVE_H_
#define SRC_MAZE_MODEL_CAVE_H_

#include <vector>
#include <string>

class Cave {
 public:
    Cave() : height_(1), width_(1) {}
    Cave(int height, int width) {generateNewCave(height, width, 50);}

    bool myRand(int percent);
    std::vector<std::vector<bool>>* getCave() {return &cave_;}
    void generateNewCave(int height, int width, int chanceToBirth);
    void createNewGeneration(int birth, int death);
    bool changeLife(int i, int j, int setting);
    void saveArea(std::string filename);
    bool openFile(std::string filename);
    std::pair<int, int> getSize();

 private:
    int height_;
    int width_;
    std::vector<std::vector<bool>> cave_;
};

#endif  // SRC_MAZE_MODEL_CAVE_H_
