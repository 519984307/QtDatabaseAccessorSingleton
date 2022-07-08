#include "databaseaccessor.h"

QMutex DatabaseAccessor::sDBMutex;
QSqlDatabase DatabaseAccessor::sDBPtr;

DatabaseAccessor::DatabaseAccessor(){
    QString pathConfig = QDir::currentPath() + "/config.ini";
    QSettings setting(pathConfig, QSettings::IniFormat);

    QString IP           = setting.value("CONNECT/IP").toString();
    QString DataBase     = setting.value("CONNECT/DataBase").toString();
    QString UserName     = setting.value("CONNECT/UserName").toString();
    QString PassWord     = setting.value("CONNECT/PassWord").toString();
    QString DataBaseType = setting.value("CONNECT/DataBaseType").toString();
    int Port             = setting.value("CONNECT/Port").toInt();

    dbHostName           = IP;
    dbName               = DataBase;
    dbUserName           = UserName;
    dbPassword           = PassWord;
    dbType               = DataBaseType;
    dbPort               = Port;

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
        QThread::msleep(1000);
        i++;
    }
}






