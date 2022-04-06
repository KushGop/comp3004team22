#include "dbmanager.h"

dbmanager::dbmanager()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("oasis.db");
    if(!db.open()){
        qDebug()<<"problem opening db";
    }

    QString query = "CREATE TABLE oasistable ("
                    "Name VARCHAR(20),"
                    "Duration integer,"
                    "Intensity integer,"
                    "CesMode VARCHAR(20),"
                    "FrequencyL integer,"
                    "FrequencyH integer);";

    QSqlQuery qry;
    if(!qry.exec(query)){
        qDebug()<<"error creating table";
    }
}

void dbmanager::addSession(QString name, int duration, int intensity,QString cesMode, int frequencyl, int frequencyh){
    QSqlQuery qry;
    qry.prepare("INSERT INTO oasistable ("
                "Name,"
                "Duration,"
                "Intensity,"
                "CesMode,"
                "FrequencyL,"
                "FrequencyH)"
                "VALUES (?,?,?,?,?,?);");

    qry.addBindValue(name);
    qry.addBindValue(duration);
    qry.addBindValue(intensity);
    qry.addBindValue(cesMode);
    qry.addBindValue(frequencyl);
    qry.addBindValue(frequencyh);

    if(!qry.exec()){
        qDebug()<<"error adding values";
    }

}

QList<Therapy*>* dbmanager::getSessions(QString name){
    QList<Therapy*>* therapies = new QList<Therapy*>;

    QSqlQuery qry;
    qry.exec("SELECT * FROM oasistable");
    while (qry.next()) {
        Therapy* therapy = new Therapy(qry.value(0).toString(), qry.value(1).toInt(), qry.value(2).toInt(),
                                       qry.value(3).toString(), qry.value(4).toInt(), qry.value(5).toInt());
        therapies->append(therapy);
    }
    return therapies;
}

bool dbmanager::deleteSession(QString name){
    QSqlQuery qry;
    qry.prepare("DELETE FROM oasistable WHERE Name=:name");
    qry.bindValue(":name",name);
    return qry.exec();
}
