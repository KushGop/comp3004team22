#ifndef THERAPY_H
#define THERAPY_H

#include <QString>
#include <QtDebug>

/*
 * Purpose: Entity class that holds relevant information about a therapy.
 *
 * Members:
 * name - The name of the specfic therapy
 * duration - How long the therapy will last for, stored in minutes
 * intensity - The intensity or strength of the stimulus
 * cesMode - The relevant session type, "Short-Pulse" or "50% Duty Cycle"
 * frequencyL - Represents the lower bound of the therapy's frequency range
 * frequencyH - Represents the upper bound of the therapy's frequency range
 *
 * Functions:
 * getters
 * setIntensity - Ensures that the intensity is not set outside of the range 1-8 inclusive
 *
 */

class Therapy
{
    public:
        Therapy(QString,int,int,QString,double,double);
        ~Therapy();

        //Remove what we don't need
        QString getName();
        int getDuration();
        int getIntensity();
        QString getCesMode();
        int getFrequencyL();
        int getFrequencyH();

        void setDuration(int);
        void setIntensity(int i);
        void setCesMode(QString c);
        void setFrequencyL(double f);
        void setFrequencyH(double f);


        void print();
        QString sessionString();

    private:
        QString name;
        int duration;
        int intensity;
        QString cesMode;
        double frequencyL;
        double frequencyH;
};

#endif // THERAPY_H
