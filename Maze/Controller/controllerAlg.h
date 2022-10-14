#ifndef SRC_MAZE_CONTROLLER_CONTROLLERALG_H_
#define SRC_MAZE_CONTROLLER_CONTROLLERALG_H_

#include "Interface/caveview.h"
#include "Interface/mazeview.h"
#include "../Model/maze.h"
#include "../Model/cave.h"

class ControllerAlgoritm {
 public:
    ControllerAlgoritm() {}
    virtual ~ControllerAlgoritm() = 0;
    virtual void saveArea(std::string filename) = 0;
    virtual void generateNew(int height, int width, int chanceToLife) = 0;
    virtual bool openReadyArea(std::string filename) = 0;
    virtual void viewSolution(int x1, int y1, int x2, int y2);
    virtual void viewGeneration(int birth, int death);
    virtual std::pair<int, int> getSize() = 0;
    virtual QGraphicsItem* getView() = 0;
    virtual QString pathToSave() = 0;
};

class ControllerMaze : public ControllerAlgoritm {
 public:
    ControllerMaze();
    ~ControllerMaze();

    void saveArea(std::string filename) override;
    void generateNew(int height, int width, int chanceToLife = 50) override;
    bool openReadyArea(std::string filename) override;
    void viewSolution(int x1, int y1, int x2, int y2) override;
    QGraphicsItem* getView() override;
    QString pathToSave() override;
    std::pair<int, int> getSize() override;

 private:
    Maze* maze;
    MazeView* view;
};


class ControllerCave : public ControllerAlgoritm {
 public:
    ControllerCave();
    ~ControllerCave();

    static int chance;

    void saveArea(std::string filename) override;
    void generateNew(int height, int width, int chanceToLife) override;
    bool openReadyArea(std::string filename) override;
    void viewGeneration(int birth, int death) override;
    QGraphicsItem* getView() override;
    QString pathToSave() override;
    std::pair<int, int> getSize() override;

 private:
    Cave* cave;
    CaveView* view;
};


#endif  // SRC_MAZE_CONTROLLER_CONTROLLERALG_H_
