#include "mainwindow.h"

#include <QApplication>

#include <QtDebug>
#include "Control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control ctrl;
    MainWindow w(&ctrl);

    w.show();
    return a.exec();
}
