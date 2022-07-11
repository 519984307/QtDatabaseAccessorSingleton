#include "databasethread.h"

DatabaseThread::DatabaseThread(){

}

void DatabaseThread::setQuery(const QString& query){
    QFuture<QVector<QVector<QVariant>>> future = QtConcurrent::run(DatabaseAccessor::executeSqlQuery, QString(query));
    future.waitForFinished();
    result = future.result();
}

QVector<QVector<QVariant>> DatabaseThread::getData(){
    return result;
}

