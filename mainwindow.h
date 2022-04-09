#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QTimer>

#include "Control.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Control *ctrl= nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Control *controller;

    QTimer pwrPress;

private slots:
    void powerShortClick();
    void powerLongClick();
    void replaceDeviceBattery();
    void intUp();
    void intDown();
    void updateClips();
    void run();

};
#endif // MAINWINDOW_H
