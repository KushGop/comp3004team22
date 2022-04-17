#ifndef CONTROL_H
#define CONTROL_H


#include <QtDebug>
#include <QString>
#include <unistd.h>

#include "Battery.h"
#include "Therapy.h"

class Control
{
    public:
        Control();
        ~Control();

        bool getSessionInProg();
        Therapy* getCurrentTherapy();

        void replaceBattery();
        bool togglePower(bool); //Use Case 2 & 3
        bool checkBatteryLevel(); //Use Case 4
        int cycleSessionGroup(int); //Use Case 5
        int cycleSessionNumber(bool); //Use Case 5

        void updateClipStatus(bool,bool); //use Case 6
        bool connectionTest(); //Use Case 6

        bool startTherapySession();
        bool runningTherapyCheck(); //Use Case 5 & Main Case
        void endTherapySession();

        void drainBattery();

        int adjustIntensity(bool); //Use Case 7

        void reset();

    private:
        Battery *battery;
        Therapy *currentTherapy;

        bool poweredOn;
        int sessionGroup; //Facilitates keeping track of the session group (duration)
        int sessionNumber; //Facilitates keeping track of the session number (type)
        bool sessionInProg;

        bool leftClip;
        bool rightClip;

        QString cesModes[8];
        int lFrequencies[8];
        int hFrequencies[8];
};

#endif // CONTROL_H
