#include "Therapy.h"

Therapy::Therapy(QString n, int d, int i, QString ces, int fL, int fH)
    :name(n), duration(d), cesMode(ces), frequencyL(fL), frequencyH(fH)
{
    setIntensity(i);
}

Therapy::~Therapy()
{
}


QString Therapy::getName()
{
    return name;
}

int Therapy::getDuration()
{
    return duration;
}

int Therapy::getIntensity()
{
    return intensity;
}

QString Therapy::getCesMode()
{
    return cesMode;
}

int Therapy::getFrequencyL()
{
    return frequencyL;
}

int Therapy::getFrequencyH()
{
    return frequencyH;
}




void Therapy::setDuration(int d)
{
    duration=d;
}

void Therapy::setIntensity(int i)
{
    if (i<1)
        intensity=1;
    else if(i>8)
        intensity=8;
    else
        intensity=i;
}


void Therapy::print()
{
    qInfo("Therapy:");
    qInfo()<<"Name: "<<name;
    qInfo()<<"Duration: "<<duration;
    qInfo()<<"Intensity: "<<intensity;
    qInfo()<<"CES Mode: "<<cesMode;
    qInfo()<<"Lower Frequency: "<<frequencyL;
    qInfo()<<"Upper Frequency: "<<frequencyH;
    qInfo("");
}
