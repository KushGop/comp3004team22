#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Control *ctrl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), controller(ctrl)
{
    ui->setupUi(this);

    //Power Button Stuff
    pwrPress.setSingleShot(true);
    connect(ui->powerButton, &QPushButton::pressed, [&]{ pwrPress.start(2000); });
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerShortClick);
    connect(&pwrPress, &QTimer::timeout, this, &MainWindow::powerLongClick);

    //Replace battery
    connect(ui->replaceBatteryButton, SIGNAL(released()), this, SLOT(replaceDeviceBattery()));

    //Int Buttons
    connect(ui->intUpButton, SIGNAL(released()), this, SLOT(intUp()));
    connect(ui->intDownButton, SIGNAL(released()), this, SLOT(intDown()));

    //Select Button
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(run()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::powerShortClick()
{

    if(pwrPress.isActive()){
        controller->cycleSessionGroup(ui->customDuration->value());
        pwrPress.stop();
    }
}

void MainWindow::powerLongClick()
{
    controller->togglePower(false);
}

void MainWindow::replaceDeviceBattery()
{
    controller->replaceBattery();
}

void MainWindow::intUp()
{
    if(controller->getSessionInProg()) //If session is going change intensity
    {
        controller->adjustIntensity(true);
    }
    else //Before session gets going change session number
        controller->cycleSessionNumber(true);

}

void MainWindow::intDown()
{
    if(controller->getSessionInProg()) //If session is going change intensity
    {
        controller->adjustIntensity(false);
    }
    else //Before session gets going change session number
        controller->cycleSessionNumber(false);
}

void MainWindow::updateClips()
{

}

void MainWindow::run()
{
   controller->runTherapySession();
}
