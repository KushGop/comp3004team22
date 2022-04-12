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
    mainRun.setSingleShot(true);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::run);
    connect(&mainRun, &QTimer::timeout, this, &MainWindow::finish);

    connect(&checkupInterval, &QTimer::timeout, this, &MainWindow::runCheckup);
    connect(&batteryDrainer, &QTimer::timeout, this, &MainWindow::batteryDrain);


    //Ear Clips
    connect(ui->leftClipSelector, SIGNAL(stateChanged(int)), this, SLOT(updateClips()));
    connect(ui->rightClipSelector, SIGNAL(stateChanged(int)), this, SLOT(updateClips()));
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
    controller->updateClipStatus(ui->leftClipSelector->isChecked(),ui->rightClipSelector->isChecked());
}

void MainWindow::run()
{
   if(controller->startTherapySession())
   {
       mainRun.start((controller->getCurrentTherapy()->getDuration())*1000);
       batteryDrainer.start(1000);
       checkupInterval.start(5000);
   }
}

void MainWindow::finish()
{
   controller->endTherapySession();
   checkupInterval.stop();
   batteryDrainer.stop();
}

void MainWindow::runCheckup()
{
   qInfo("DELETE: Checkup called");
   if(!controller->runningTherapyCheck())
   {
       mainRun.stop();
       checkupInterval.stop();
       batteryDrainer.stop();
   }
}

void MainWindow::batteryDrain()
{
   controller->drainBattery();
}
