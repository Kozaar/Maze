#ifndef SRC_MAZE_INTERFACE_MAZEVIEW_H_
#define SRC_MAZE_INTERFACE_MAZEVIEW_H_

#include <QGraphicsItem>
#include <QPainter>
#include <vector>

class MazeView : public QGraphicsItem {
 public:
    MazeView() : QGraphicsItem() {solutionView_ = false;}
    explicit MazeView(std::vector<std::vector<std::pair<bool, bool>>>* walls);
    void solutionView(bool solutionView) {solutionView_ = solutionView;}
    void solution(std::vector<std::pair<int, int>>* solution) {solution_ = solution;}
    void walls(std::vector<std::vector<std::pair<bool, bool>>>* walls) {walls_ = walls;}

 protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

 private slots:
    void drawMaze(QPainter *painter);
    void drawSolution(QPainter *painter);

 private:
    bool solutionView_;
    std::vector<std::vector<std::pair<bool, bool>>>* walls_;
    std::vector<std::pair<int, int>>* solution_;
};

#endif  // SRC_MAZE_INTERFACE_MAZEVIEW_H_
