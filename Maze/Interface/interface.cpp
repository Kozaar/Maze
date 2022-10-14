#include "interface.h"
#include "ui_interface.h"
#include <QFileDialog>
#include <iostream>

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface) {
    ui->setupUi(this);
    timer = new QTimer(this);
    scene = new Scene();
    ui->viewWidget->setScene(scene);
    ui->viewWidget->centerOn(ui->viewWidget->width()/2, ui->viewWidget->height()/2);
    ui->viewWidget->setSceneRect(0, 0, ui->viewWidget->width()-2, ui->viewWidget->height()-2);
    controllers[0] = new ControllerMaze;
    controllers[1] = new ControllerCave;
    for (size_t i = 0; i < controllers.size(); i++) {
        scene->addItem(controllers[i]->getView());
    }
    drawBorders();
    on_mazeRadioButton_clicked();
    connect(scene, SIGNAL(viewSolutionSignal(double, double, double, double)),
            this, SLOT(viewMazeSolution(double, double, double, double)));
    connect(scene, SIGNAL(eraseSolution()), this, SLOT(on_MazePushButtonClear_clicked()));
}


Interface::~Interface() {
    for (size_t i = 0; i < controllers.size(); i++) {
        delete controllers[i];
    }
    delete ui;
}


void Interface::drawBorders() {
    QPen pen;
    pen.setWidth(2);
    scene->addRect(0, 0, ui->viewWidget->sceneRect().width(), ui->viewWidget->sceneRect().height(), pen);
    scene->setBackgroundBrush(Qt::white);
}


void Interface::on_caveRadioButton_clicked() {
    checkTimer();
    ui->caveRadioButton->setChecked(true);
    ui->solutionStackedWidget->setCurrentIndex(0);
    controllers[CAVE]->getView()->setVisible(true);
    controllers[MAZE]->getView()->setVisible(false);
    currentController = controllers[CAVE];
}


void Interface::on_mazeRadioButton_clicked() {
    checkTimer();
    ui->mazeRadioButton->setChecked(true);
    ui->solutionStackedWidget->setCurrentIndex(1);
    controllers[MAZE]->getView()->setVisible(true);
    controllers[MAZE]->getView()->grabMouse();
    controllers[CAVE]->getView()->setVisible(false);
    currentController = controllers[MAZE];
}


void Interface::on_MazePushButtonViewSolution_clicked() {
    currentController->viewSolution(ui->MazeSpinBoxX1->value()-1,
                                    ui->MazeSpinBoxY1->value()-1,
                                    ui->MazeSpinBoxX2->value()-1,
                                    ui->MazeSpinBoxY2->value()-1);
    scene->update();
}


void Interface::viewMazeSolution(double x1, double y1, double x2, double y2) {
    double StepY = 500/(double)currentController->getSize().first;
    double StepX = 500/(double)currentController->getSize().second;
    currentController->viewSolution(x1/StepX,
                                    y1/StepY,
                                    x2/StepX,
                                    y2/StepY);
    scene->update();
}

void Interface::on_pushButtonGenerate_clicked() {
    checkTimer();
    currentController->generateNew(ui->heightSpinbox->value(),
                                   ui->widthSpinbox->value(),
                                   ui->spinBoxCaveChance->value());
    setMaximumValueSpinBox();
    scene->update();
}


void Interface::on_pushButtonOpen_clicked() {
    checkTimer();
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Open File", currentController->pathToSave(),
                                            "Text files (*.txt)");
    if (filename != nullptr) {
        if (currentController->openReadyArea(filename.toStdString())) {
            ui->heightSpinbox->setValue(currentController->getSize().first);
            ui->widthSpinbox->setValue(currentController->getSize().second);
            setMaximumValueSpinBox();
            scene->update();
        } else {
            ui->labelFileCondition->setText("File is invalid");
        }
    }
}


void Interface::on_pushButtonSave_clicked() {
    checkTimer();
    QString format = "txt";
    QString default_path = currentController->pathToSave();
    QFileDialog save_dialog(this, tr("Сохранить как"), default_path);
    save_dialog.setAcceptMode(QFileDialog::AcceptSave);
    save_dialog.setDirectory(default_path);
    save_dialog.setDefaultSuffix(format);
    const QStringList filter("Text files (*.txt)");
    save_dialog.setMimeTypeFilters(filter);
    if (save_dialog.exec() == QDialog::Accepted) {
        const QString fname = save_dialog.selectedFiles().constFirst();
         currentController->saveArea(fname.toStdString());
    }
}


void Interface::on_pushbattonCaveNextGen_clicked() {
    checkTimer();
    createNewGeneration();
}


void Interface::on_pushbattonCaveAutomatic_clicked() {
    if (!timer->isActive()) {
        ui->pushbattonCaveAutomatic->setText("STOP");
        connect(timer, SIGNAL(timeout()), this, SLOT(createNewGeneration()));
        timer->start(ui->spinBoxCaveStep->value());
    } else {
        checkTimer();
    }
}


void Interface::checkTimer() {
    if (timer->isActive()) {
        ui->pushbattonCaveAutomatic->setText("Automatic operation");
        timer->stop();
    }
    ui->labelFileCondition->clear();
}


void Interface::setMaximumValueSpinBox() {
    ui->MazeSpinBoxY1->setMaximum(currentController->getSize().first);
    ui->MazeSpinBoxY2->setMaximum(currentController->getSize().second);
    ui->MazeSpinBoxX1->setMaximum(currentController->getSize().first);
    ui->MazeSpinBoxX2->setMaximum(currentController->getSize().second);
}


void Interface::createNewGeneration() {
    currentController->viewGeneration(ui->spinBoxCaveBirth->value(), ui->spinBoxCaveDeath->value());
    scene->update();
}

void Interface::on_MazePushButtonClear_clicked() {
    scene->update();
}
