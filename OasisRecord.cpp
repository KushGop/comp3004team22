#include "OasisRecord.h"

oasisRecord::oasisRecord(const QString& sessionType, const int intensityLevel, const int duration) {
    this->sessionType = sessionType;
    this->intensityLevel = intensityLevel;
    this->duration = duration;

}

//Display String
QString oasisRecord::toString() {
    QString displayInfo =
              "Session Type: " + sessionType + "\n"
            + "Intensity Level: " + intensityLevel + "\n"
            + "Duration: " + duration + "\n";
    return displayInfo;
}

//Session Type
QString oasisRecord::getSessionType() { 
    return sessionType; 
}

//Duration
void oasisRecord::setDuration(int d) { 
    duration = d; 
}

int oasisRecord::getDuration() { 
    return duration; 
}

//IntensityLevel
void oasisRecord::setIntensityLevel(int i) { 
    intensityLevel = i; 
}

int oasisRecord::getIntensityLevel() { 
    return intensityLevel; 
}


