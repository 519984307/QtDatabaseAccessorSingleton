#include "databaseaccessor.h"

QMutex DatabaseAccessor::sDBMutex;
QSqlDatabase DatabaseAccessor::sDBPtr;

DatabaseAccessor::DatabaseAccessor(){
    QString pathConfig = QDir::currentPath() + "/config.ini";
    QSettings setting(pathConfig, QSettings::IniFormat);

    dbHostName = setting.value("CONNECT/IP").toString();
    dbName     = setting.value("CONNECT/Database").toString();
    dbUserName = setting.value("CONNECT/Username").toString();
    dbPassword = setting.value("CONNECT/Password").toString();
    dbType     = setting.value("CONNECT/DatabaseType").toString();
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

QVector<QVector<QVariant>> DatabaseAccessor::executeSqlQuery(const QString& query){
    QVector<QVector<QVariant>> result;
    QSqlQuery sqlQuery( DatabaseAccessor::getInstance()->sDBPtr);
    sqlQuery.exec(query);

    while(sqlQuery.next()){
        QVector<QVariant> collum;
        for(int j = 0; j < sqlQuery.record().count(); j++){
            collum.append(sqlQuery.value(j));
        }
        result.append(collum);
    }
    qDebug() << "QThread: " << QThread::currentThread();

    return result;
}






