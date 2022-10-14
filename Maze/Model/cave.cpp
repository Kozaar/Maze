#include "cave.h"
#include "cavefile.h"

bool Cave::myRand(int chanceToBirth) {
    return arc4random_uniform(100) < (uint32_t)chanceToBirth;
}

void Cave::generateNewCave(int height, int width, int chanceToBirth) {
    height_ = height;
    width_ = width;
    cave_.clear();
    std::vector<bool> buf;
    for (int i = 0; i < height_; i++) {
        buf.clear();
        for (int j = 0; j < width_; j++) {
            buf.push_back(myRand(chanceToBirth));
        }
        cave_.push_back(buf);
    }
}

void Cave::createNewGeneration(int birth, int death) {
    std::vector<std::vector<bool>> newcave(cave_);
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            if (!cave_[i][j]) {
                newcave[i][j] = changeLife(i, j, birth);
            } else {
                newcave[i][j] = changeLife(i, j, death-1);
            }
        }
    }
    cave_.swap(newcave);
}

bool Cave::changeLife(int i, int j, int setting) {
    int sum = 0;
    if (cave_[(i-1+height_)%height_][(j-1+width_)%width_]) sum++;
    if (cave_[(i-1+height_)%height_][(j)%width_]) sum++;
    if (cave_[(i-1+height_)%height_][(j+1)%width_]) sum++;
    if (cave_[(i)%height_][(j-1+width_)%width_]) sum++;
    if (cave_[(i)%height_][(j+1)%width_]) sum++;
    if (cave_[(i+1)%height_][(j-1+width_)%width_]) sum++;
    if (cave_[(i+1)%height_][(j)%width_]) sum++;
    if (cave_[(i+1)%height_][(j+1)%width_]) sum++;
    return (sum > setting);
}

bool Cave::openFile(std::string filename) {
    bool res = Cavefile::getDataFromFile(filename, &cave_);
    if (res) {
        height_ = cave_.at(0).size();
        width_ = cave_.size();
    }
    return res;
}


std::pair<int, int> Cave::getSize() {
    return {height_, width_};
}


void Cave::saveArea(std::string filename) {
    Cavefile::setInFile(filename, cave_);
}
