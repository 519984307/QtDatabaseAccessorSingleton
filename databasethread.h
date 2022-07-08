#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QString>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include "databaseaccessor.h"

class DatabaseThread : public QThread{
    Q_OBJECT
public:
    DatabaseThread();

protected slots:
    void process();

signals:
    void executeSqlQuery(QString);
};

#endif // DATABASETHREAD_H
