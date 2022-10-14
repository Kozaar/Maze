#ifndef SRC_MAZE_INTERFACE_SCENE_H_
#define SRC_MAZE_INTERFACE_SCENE_H_

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


class Scene : public QGraphicsScene {
    Q_OBJECT

 public:
    Scene() : QGraphicsScene() {mouseCoord = {-1, -1};}

 signals:
    void viewSolutionSignal(double x1, double y1, double x2, double y2);
    void eraseSolution();

 protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

 private:
    std::pair<double, double> mouseCoord;
};

#endif  // SRC_MAZE_INTERFACE_SCENE_H_
