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

    //Record
    connect(ui->recordButton, SIGNAL(released()),this,SLOT(record()));

    //Ear Clips
    connect(ui->leftClipSelector, SIGNAL(stateChanged(int)), this, SLOT(updateClips()));
    connect(ui->rightClipSelector, SIGNAL(stateChanged(int)), this, SLOT(updateClips()));

    //UI helper
    times={
        ui->time_20,
        ui->time_45,
        ui->time_custom
    };
    types = {
        ui->session1,
        ui->session2,
        ui->session3,
        ui->session4,
        ui->session5,
        ui->session6,
        ui->session7,
        ui->session8
    };
    intensities = {
        ui->intense_1,
        ui->intense_2,
        ui->intense_3,
        ui->intense_4,
        ui->intense_5,
        ui->intense_6,
        ui->intense_7,
        ui->intense_8
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::powerShortClick()
{

    if(pwrPress.isActive()){
        int time = controller->cycleSessionGroup(ui->customDuration->value());
        pwrPress.stop();
        if(time-1==-1){
            times[2]->setStyleSheet("color:black");
        }else{
            times[time-1]->setStyleSheet("color:black");
        }
        times[time]->setStyleSheet("color:green");
    }
}

void MainWindow::powerLongClick()
{

    if(controller->togglePower(false)){
        times[0]->setStyleSheet("color:green");
        types[0]->setStyleSheet("color:green");
        intensities[0]->setStyleSheet("color:green");
    }else{
        for(int i=0;i<8;i++){
        types[i]->setStyleSheet("color:black");
        intensities[i]->setStyleSheet("color:black");
        }
        for(int i=0;i<3;i++)
            times[i]->setStyleSheet("color:black");
    }
}

void MainWindow::replaceDeviceBattery()
{
    controller->replaceBattery();
}

void MainWindow::intUp()
{
    if(controller->getSessionInProg()) //If session is going change intensity
    {
        int intensity = controller->adjustIntensity(true);
        for(int i=0;i<intensity;i++)
            intensities[i]->setStyleSheet("color:green");

    }
    else{ //Before session gets going change session number
        int ses = controller->cycleSessionNumber(true);
        if(ses-1==-1){
            types[7]->setStyleSheet("color:black");
        }else{
            types[ses-1]->setStyleSheet("color:black");
        }
        types[ses]->setStyleSheet("color:green");
    }

}

void MainWindow::intDown()
{
    if(controller->getSessionInProg()) //If session is going change intensity
    {
        int intensity = controller->adjustIntensity(false);
        intensities[intensity]->setStyleSheet("color:black");
    }
    else{ //Before session gets going change session number
        int ses = controller->cycleSessionNumber(false);
        if(ses==7){
            types[0]->setStyleSheet("color:black");
        }else{
            types[ses+1]->setStyleSheet("color:black");
        }
        types[ses]->setStyleSheet("color:green");
    }
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

void MainWindow::record()
{
    qInfo("RECORDING SESSION");
    QString s = controller->getCurrentTherapy()->sessionString();
    QFile file(fn);
    if(file.open(QIODevice::WriteOnly|QIODevice::Append)){
        QTextStream stream(&file);
        stream <<qPrintable(s)<<endl;
    }
}
