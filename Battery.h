#ifndef BATTERY_H
#define BATTERY_H

#include <QString>

class Battery {

public:
    
    //Constructor
    Battery(QString& batteryStaus, double batteryLevel);

    //Battery Level
    void setBatteryLevel(double);
    double getBatteryLevel();
    
    //BatteryStatus
    //void setBatteryStatus(QString&); --- maybe?
    QString getBatteryStatus();
    

private:
    QString batteryStatus;
    double batteryLevel;
};

#endif // Battery_H
