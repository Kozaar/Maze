#include "scene.h"

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() != Qt::LeftButton) {
        mouseCoord = {-1., -1.};
        emit eraseSolution();
    } else if (mouseCoord.first != -1) {
        emit viewSolutionSignal(mouseCoord.first,
                                mouseCoord.second,
                                event->lastScenePos().x(),
                                event->lastScenePos().y());
        mouseCoord = {-1., -1.};
    } else {
        mouseCoord = {event->lastScenePos().x(), event->lastScenePos().y()};
    }
}
