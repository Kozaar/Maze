#ifndef SRC_MAZE_MODEL_MAZEFILE_H_
#define SRC_MAZE_MODEL_MAZEFILE_H_

#include <string>
#include <vector>

class MazeFile {
 public:
    MazeFile() {}

    static bool getMazeDataFromFile(std::string fileName,
                                    std::vector<std::vector<std::pair<bool, bool> > > *data);
    static void setMazeInFile(std::string fileName,
                              const std::vector<std::vector<std::pair<bool, bool> > > &vectorForWrite);
};

#endif  //  SRC_MAZE_MODEL_MAZEFILE_H_
