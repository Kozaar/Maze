#include "caveview.h"
#include <iostream>

CaveView::CaveView(std::vector<std::vector<bool>>* field)
    : QGraphicsItem() {
    field_ = field;
}

void CaveView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawCave(painter);
}

QRectF CaveView::boundingRect() const {
    return QRectF(0, 0, 500, 500);
}

void CaveView::drawCave(QPainter *painter) {
    int rows = field_->size();
    int cols = field_->at(0).size();
    double stepY = 500/(double)rows;
    double stepX = 500/(double)cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field_->at(i)[j]) {
                QRectF rect(stepX*j, stepY*i, stepX, stepY);
                painter->fillRect(rect, Qt::black);
            }
        }
    }
}
