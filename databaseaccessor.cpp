#include "databaseaccessor.h"

QMutex DatabaseAccessor::sDBMutex;
QSqlDatabase DatabaseAccessor::sDBPtr;

DatabaseAccessor::DatabaseAccessor(){
    QString pathConfig = QDir::currentPath() + "/config.ini";
    QSettings setting(pathConfig, QSettings::IniFormat);

    dbHostName = setting.value("CONNECT/IP").toString();
    dbName     = setting.value("CONNECT/DataBase").toString();
    dbUserName = setting.value("CONNECT/UserName").toString();
    dbPassword = setting.value("CONNECT/PassWord").toString();
    dbType     = setting.value("CONNECT/DataBaseType").toString();
    dbPort     = setting.value("CONNECT/Port").toInt();

    sDBPtr = QSqlDatabase::addDatabase(dbType);

    sDBPtr.setHostName(dbHostName);
    sDBPtr.setDatabaseName(dbName);
    sDBPtr.setUserName(dbUserName);
    sDBPtr.setPassword(dbPassword);
    sDBPtr.setPort(dbPort);
    if (!sDBPtr.open()){
        qDebug() << "Open datatabase error:" << sDBPtr.lastError().text();
    }else{
        qDebug() << "Datatabase is open";
    }
}

DatabaseAccessor* DatabaseAccessor::getInstance(){
    static DatabaseAccessor instance;
    return &instance;
}

void DatabaseAccessor::executeSqlQuery(QString query){
    int i = 0;

    emit finished();
    while (i < 10000){
        QSqlQuery sqlQuery(sDBPtr);
        sqlQuery.exec(query);

        while (sqlQuery.next()){
            qDebug() << "thread1 value:" << sqlQuery.value(0).toString();
        }
        QThread::msleep(10);
        i++;
    }
}






