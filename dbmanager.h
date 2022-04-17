#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QDebug>
#include <QFileInfo>

#include "Therapy.h"
#include "OasisRecord.h"
#include "Battery.h"

class dbmanager
{
public:
    dbmanager();
    void addSession(QString name, int duration, int intensity,QString cesMode, int frequencyl, int frequencyh);
    QList<Therapy*>* getSessions(QString name);
    bool deleteSession(QString name);
};

#endif // DBMANAGER_H
