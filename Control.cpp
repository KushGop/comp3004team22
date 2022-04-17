#include "Control.h"


Control::Control()
    : poweredOn(false), sessionGroup(1), sessionNumber(0), sessionInProg(false), leftClip(false), rightClip(false)
{
    battery = new Battery(100.0);
    currentTherapy = new Therapy("Custom",20,4,"MET",0.5,3);

    cesModes[0]="MET";
    cesModes[1]="Sub-Delta";
    cesModes[2]="Delta";
    cesModes[3]="Theta";
    cesModes[4]="Alpha";
    cesModes[5]="SMR";
    cesModes[6]="Beta";
    cesModes[7]="100 Hz";

    lFrequencies[0]=0.5;
    lFrequencies[1]=0.5;
    lFrequencies[2]=2.5;
    lFrequencies[3]=6;
    lFrequencies[4]=9;
    lFrequencies[5]=12;
    lFrequencies[6]=18;
    lFrequencies[7]=100;

    hFrequencies[0]=3;
    hFrequencies[1]=3;
    hFrequencies[2]=5;
    hFrequencies[3]=8;
    hFrequencies[4]=11;
    hFrequencies[5]=15;
    hFrequencies[6]=22;
    hFrequencies[7]=100;
}

Control::~Control()
{
    delete battery;
    delete currentTherapy;
}


bool Control::getSessionInProg()
{
    return sessionInProg;
}

Therapy* Control::getCurrentTherapy()
{
    return currentTherapy;
}


void Control::replaceBattery()
{
    battery->setBatteryLevel(100.0); //For simplicity
    qInfo("Battery replacement successful");
    qInfo(" ");
}

//Use Case 2 & 3
bool Control::togglePower(bool critShutdown)
{
    if(poweredOn&&critShutdown)
    {
        qInfo("Battery Level Critically Low: Shutting Down");
        poweredOn=false;
        sessionInProg=false;
        reset();
        return false;
    }

    if(poweredOn)
    {
        qInfo("Shutting Down");
        poweredOn=false;
        sessionInProg=false;
        reset();
    }
    else
    {
        qInfo("Turning On");
        poweredOn=true;
        sessionInProg=false;
        checkBatteryLevel();
    }

    qInfo(" ");
    return poweredOn;
}

//Use Case 4
bool Control::checkBatteryLevel()
{
    if(!poweredOn)
    {
        qInfo("ERROR: Cannot check battery level when device is off");
        return false;
    }

    if(poweredOn && battery->batteryLevelCritical())
    {
        togglePower(true);
        return false;
    }

    if(poweredOn && battery->batteryLevelLow())
    {
        qInfo("Battery Level Low");
    }

    qInfo()<<"Current Battery Level: "<<battery->getBatteryLevel();
    return true;
}

//Use Case 5
int Control::cycleSessionGroup(int cus)
{
    if(!poweredOn || sessionInProg)
    {
        qInfo("ERROR: Cannot change session group when device is off or session is in progress");
        return -1;
    }

    sessionGroup+=1; //Cycling

    if(sessionGroup>3) //Ensuring sessionGroup stays in the range 1-3
        sessionGroup=1;

    if(sessionGroup==1)
    {
        currentTherapy->setDuration(20);
        qInfo()<<"Therapy duration set to 20 minutes";
        return 0;
    }

    if(sessionGroup==2)
    {
        currentTherapy->setDuration(45);
        qInfo()<<"Therapy duration set to 45 minutes";
        return 1;
    }

    if(sessionGroup==3)
    {
        currentTherapy->setDuration(cus);
        qInfo()<<"Therapy duration set to "<<cus<<" minutes";
        return 2;
    }
    return sessionGroup-1;
}

//Use Case 5
int Control::cycleSessionNumber(bool upArrow) //upArrow is true when the up INT button is pressed
{
    if(!poweredOn || sessionInProg)
    {
        qInfo("ERROR: Cannot change session number when device is off or session is in progress");
        return -1;
    }

    if(upArrow)
    {
        sessionNumber = (sessionNumber+1)%8;
        qInfo()<<"DELETE: Session Number is now "<<sessionNumber;
    }
    else
    {
        sessionNumber -= 1;
        if(sessionNumber<0) //Ensuring sessionNumber stays in the range 0-7
            sessionNumber=7;
        qInfo()<<"DELETE: Session Number is now "<<sessionNumber;
    }

    currentTherapy->setCesMode(cesModes[sessionNumber]);
    currentTherapy->setFrequencyL(lFrequencies[sessionNumber]);
    currentTherapy->setFrequencyH(hFrequencies[sessionNumber]);
    return sessionNumber;
}

void Control::updateClipStatus(bool left, bool right)
{
    leftClip=left;
    rightClip=right;
    qInfo()<<"DELETE: Current Clip Status "<<leftClip<<" and "<<rightClip;
}

bool Control::connectionTest()
{
    return (leftClip && rightClip);
}

bool Control::startTherapySession()
{
    if(!poweredOn)
    {
        qInfo("ERROR: Cannot run session when device is off");
        return false;
    }

    if(sessionInProg)
    {
        qInfo("ERROR: Session already in progress");
        return false;
    }

    if(!connectionTest())
    {
        qInfo("ERROR: Please connect both ear clips");
        return false;
    }

    qInfo(" ");
    qInfo("Starting Session:");
    currentTherapy->print();
    sessionInProg=true;
    return true;


}

bool Control::runningTherapyCheck()
{
    if(!poweredOn)
    {
        qInfo("ERROR: Cannot run session when device is off");
        return false;
    }

    if(!sessionInProg)
    {
        qInfo("ERROR: Session not in progress");
        return false;
    }

    if(!checkBatteryLevel())
        return false;

    return true;
}

void Control::endTherapySession()
{

    qInfo("Session Complete");
    sessionInProg=false;
    togglePower(false);
}

void Control::drainBattery()
{
    battery->drainBattery(currentTherapy->getIntensity());
}

//Use Case 7
int Control::adjustIntensity(bool upArrow) //upArrow is true when the up INT button is pressed)
{
    int cIntensity=currentTherapy->getIntensity();

    if(!poweredOn || !sessionInProg)
    {
        qInfo("ERROR: Cannot change session intensity when device is off or session is not in progress");
        return currentTherapy->getIntensity();
    }


    if(upArrow)
        cIntensity++;
    else
        cIntensity--;


    if (cIntensity<1) //Ensuring cIntensity stays in the range 1-8
        cIntensity=1;
    else if(cIntensity>8)
        cIntensity=8;

    currentTherapy->setIntensity(cIntensity);
    qInfo()<<"DELETE: Intensity is now "<<currentTherapy->getIntensity();
    return currentTherapy->getIntensity();
}

void Control::reset()
{
    sessionGroup=0;
    sessionNumber=0;
    currentTherapy->setIntensity(1);
}
