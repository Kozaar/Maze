#ifndef SRC_MAZE_MODEL_CAVEFILE_H_
#define SRC_MAZE_MODEL_CAVEFILE_H_
#include <vector>
#include <string>

class Cavefile {
 public:
    static bool getDataFromFile(std::string filename, std::vector<std::vector<bool>>* data);
    static void setInFile(std::string filename, const std::vector<std::vector<bool>>& data);
    static void getSizeFromFile(std::ifstream* fin, int* rows, int* cols);
};

#endif  // SRC_MAZE_MODEL_CAVEFILE_H_
