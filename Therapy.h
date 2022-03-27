#ifndef THERAPY_H
#define THERAPY_H

#include <QString>

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
        Therapy(QString,int,int,QString,int,int);
        ~Therapy();

        //Remove what we don't need
        QString getName();
        int getDuration();
        int getIntensity();
        QString getCesMode();
        int getFrequencyL();
        int getFrequencyH();

    private:
        QString name;
        int duration;
        int intensity;
        QString cesMode;
        int frequencyL;
        int frequencyH;

        //If we decide to make this dynamic it can just be moved to public
        void setIntensity(int i);
};

#endif // THERAPY_H
