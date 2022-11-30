#include "Interface/interface.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    QApplication a(argc, argv);
    Interface w;
    w.show();
    return a.exec();
}
