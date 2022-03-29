#ifndef OASIS_RECORD_H
#define OASIS_RECORD_H

#include <QString>

class oasisRecord {

public:

    //Constructor
    oasisRecord(const QString& sessionType, const int intensityLevel, const int duration);
    
    //Session Type
    QString getSessionType();

    //Intensity Level
    void setIntensityLevel(int i);
    int getIntensityLevel();

    //Duration
    void setDuration(int durationMS);
    int getDuration();
    
    QString toString();

private:
    QString sessionType;
    int intensityLevel;
    int duration;

};

#endif // OASIS_RECORD_H