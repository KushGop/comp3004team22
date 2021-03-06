#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QTimer>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include "Control.h"
#include "Therapy.h"

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
    QTimer mainRun;
    QTimer checkupInterval;
    QTimer batteryDrainer;

    QList<QLabel *> times;
    QList<QLabel *> types;
    QList<QLabel *> intensities;

private slots:
    void powerShortClick();
    void powerLongClick();
    void replaceDeviceBattery();
    void intUp();
    void intDown();
    void updateClips();
    void run();
    void finish();
    void runCheckup();
    void batteryDrain();
    void record();
};
#endif // MAINWINDOW_H
