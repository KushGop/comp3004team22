#include "Battery.h"

Battery::Battery(double batteryLevel){
    this->batteryLevel = batteryLevel;
}

//Battery Status
/*
void Battery::setBatteryStatus(QString& bs) { 
    batteryStatus = bs; 
}

QString Battery::getBatteryStatus(){
    return batteryStatus;
}
*/

//Battery Level
void Battery::setBatteryLevel(double bl){
    batteryLevel = bl;
}
double Battery::getBatteryLevel(){
    return batteryLevel;
}


bool Battery::batteryLevelLow()
{
    return batteryLevel<=20.0;
}

bool Battery::batteryLevelCritical()
{
    return batteryLevel<=5.0;
}

void Battery::drainBattery(int power)
{
    //Will be called on each iteration, drains up to 1% per iteration

    if(power>8)
        power=8;

    if(power<1)
        power=1;

    batteryLevel-=(power/8);
}
