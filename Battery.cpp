#include "Battery.h"

Battery::Battery(QString& batteryStatus, double batteryLevel){
    this->batteryStatus = batteryStatus;
    this->batteryLevel = batteryLevel;
}

//Battery Status
/*
void Battery::setBatteryStatus(QString& bs) { 
    batteryStatus = bs; 
}
*/
QString Battery::getBatteryStatus(){
    return batteryStatus;
}

//Battery Level
void Battery::setBatteryLevel(double bl){
    batteryLevel = bl;
}
double Battery::getBatteryLevel(){
    return batteryLevel;
}
