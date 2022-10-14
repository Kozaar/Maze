#include "mazeview.h"

MazeView::MazeView(std::vector<std::vector<std::pair<bool, bool>>>* walls)
    : QGraphicsItem() {
    solutionView_ = false;
    walls_ = walls;
}

void MazeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    drawMaze(painter);

    if (solutionView_) {
        drawSolution(painter);
        solutionView_ = false;
    }
}

QRectF MazeView::boundingRect() const {
    return QRectF(0, 0, 500, 500);
}

void MazeView::drawMaze(QPainter *painter) {
    int rows = walls_->size();
    int cols = walls_->at(0).size();
    double stepY = 500/(double)rows;
    double stepX = 500/(double)cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (walls_->at(i)[j].first) {
                QLineF line((j+1)*stepX, i*stepY, (j+1)*stepX, (i+1)*stepY);
                painter->drawLine(line);
            }
            if (walls_->at(i)[j].second) {
                QLineF line(j*stepX, (i+1)*stepY, (j+1)*stepX,
                            (i+1)*stepY);
                painter->drawLine(line);
            }
        }
    }
}

void MazeView::drawSolution(QPainter *painter) {
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    double stepY = 500/(double)walls_->size();
    double stepX = 500/(double)walls_->at(0).size();
    auto it = solution_->begin();
    painter->drawPoint(it->first*stepX+stepX/2, it->second*stepY+stepY/2);
    for (it++; it != solution_->end(); it++) {
        QLineF line((it-1)->first*stepX+stepX/2,
                    (it-1)->second*stepY+stepY/2,
                    it->first*stepX+stepX/2,
                    it->second*stepY+stepY/2);
        painter->drawLine(line);
    }
}


