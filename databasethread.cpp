#include "databasethread.h"

DatabaseThread::DatabaseThread(){
    connect(this, SIGNAL(executeSqlQuery(QString)),
            DatabaseAccessor::getInstance(), SLOT(executeSqlQuery(QString)));

    QThread* thread = new QThread;
    DatabaseAccessor::getInstance()->moveToThread(thread);
    connect(thread, SIGNAL(started()), this, SLOT(process()));
    thread->start();
}

void DatabaseThread::process(){
    emit executeSqlQuery("SELECT login FROM users");
}

