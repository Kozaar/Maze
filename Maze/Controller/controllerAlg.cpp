#include "controllerAlg.h"

// ----------------------------------------------------
// ControllerMaze metods
// ----------------------------------------------------
ControllerMaze::ControllerMaze() : ControllerAlgoritm() {
        maze = new Maze;
        maze->generate(6, 6);
        view = new MazeView(maze->getMaze());
}

ControllerMaze::~ControllerMaze() {
    delete maze;
    delete view;
}

void ControllerMaze::saveArea(std::string filename) {
    maze->saveInFile(filename);
}

void ControllerMaze::generateNew(int height, int width, int chanceToLife) {
    Q_UNUSED(chanceToLife);
    maze->generate(height, width);
}

bool ControllerMaze::openReadyArea(std::string filename) {
    return maze->openFile(filename);
}

void ControllerMaze::viewSolution(int x1, int y1, int x2, int y2) {
    maze->findSolution(x1, y1, x2, y2);
    view->solutionView(true);
    view->solution(maze->getSolutionMaze());
}

QGraphicsItem* ControllerMaze::getView() {
    return view;
}

QString ControllerMaze::pathToSave() {
    return "examples/maze";
}


std::pair<int, int> ControllerMaze::getSize() {
    return maze->getSize();
}

// ----------------------------------------------------
// ControlerCave metods
// ----------------------------------------------------
ControllerCave::ControllerCave() : ControllerAlgoritm() {
    cave = new Cave(6, 6);
    view = new CaveView(cave->getCave());
}


ControllerCave::~ControllerCave() {
    delete cave;
    delete view;
}


void ControllerCave::saveArea(std::string filename) {
    cave->saveArea(filename);
}


void ControllerCave::generateNew(int height, int width, int chanceToLife) {
    cave->generateNewCave(height, width, chanceToLife);
}


bool ControllerCave::openReadyArea(std::string filename) {
    return cave->openFile(filename);
}


void ControllerCave::viewGeneration(int birth, int death) {
    cave->createNewGeneration(birth, death);
}


QGraphicsItem* ControllerCave::getView() {
    return view;
}

QString ControllerCave::pathToSave() {
    return "examples/cave";
}

std::pair<int, int> ControllerCave::getSize() {
    return cave->getSize();
}

// ----------------------------------------------------
// Virtual metods
// ----------------------------------------------------
void ControllerAlgoritm::viewSolution(int x1, int y1, int x2, int y2) {Q_UNUSED(x1);
                                                                       Q_UNUSED(y1);
                                                                       Q_UNUSED(x2);
                                                                       Q_UNUSED(y2);}
void ControllerAlgoritm::viewGeneration(int birth, int death) {Q_UNUSED(birth);
                                                               Q_UNUSED(death);}
ControllerAlgoritm::~ControllerAlgoritm() {}
