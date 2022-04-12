#ifndef BATTERY_H
#define BATTERY_H

#include <QString>

class Battery {

public:
    
    //Constructor
    Battery(double batteryLevel);

    //Battery Level
    void setBatteryLevel(double);
    double getBatteryLevel();
    
    //BatteryStatus
    //void setBatteryStatus(QString&); --- maybe?
    //QString getBatteryStatus();

    bool batteryLevelLow();
    bool batteryLevelCritical();

    void drainBattery(int);
    

private:
    double batteryLevel;
};

#endif // Battery_H
