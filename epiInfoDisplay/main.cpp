#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setOverrideCursor(Qt::BlankCursor);
    w.show();

    return a.exec();
}
