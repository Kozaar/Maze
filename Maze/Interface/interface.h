#ifndef SRC_MAZE_INTERFACE_INTERFACE_H_
#define SRC_MAZE_INTERFACE_INTERFACE_H_

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "../Controller/controllerAlg.h"
#include "scene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QMainWindow {
    Q_OBJECT

 public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

 public slots:
    void viewMazeSolution(double x1, double y1, double x2, double y2);

 private slots:
    void drawBorders();
    void on_caveRadioButton_clicked();
    void on_mazeRadioButton_clicked();
    void on_pushbattonCaveAutomatic_clicked();
    void on_MazePushButtonViewSolution_clicked();
    void on_pushButtonGenerate_clicked();
    void on_pushButtonOpen_clicked();
    void on_pushButtonSave_clicked();
    void on_pushbattonCaveNextGen_clicked();
    void checkTimer();
    void setMaximumValueSpinBox();
    void createNewGeneration();
    void on_MazePushButtonClear_clicked();

 private:
    Ui::Interface *ui;
    Scene* scene;
    std::map<int, ControllerAlgoritm*> controllers;
    ControllerAlgoritm* currentController;
    QTimer* timer;

    static constexpr int MAZE = 0;
    static constexpr int CAVE = 1;
};
#endif  // SRC_MAZE_INTERFACE_INTERFACE_H_
