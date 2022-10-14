#ifndef SRC_MAZE_INTERFACE_CAVEVIEW_H_
#define SRC_MAZE_INTERFACE_CAVEVIEW_H_

#include <QGraphicsItem>
#include <QPainter>
#include <vector>

class CaveView : public QGraphicsItem {
 public:
    CaveView() : QGraphicsItem() {}
    explicit CaveView(std::vector<std::vector<bool>>* field);
    void field(std::vector<std::vector<bool>>* field) {field_ = field;}

 protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void drawCave(QPainter *painter);

 private:
    std::vector<std::vector<bool>>* field_;
};

#endif  // SRC_MAZE_INTERFACE_CAVEVIEW_H_
