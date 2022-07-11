#include "client.h"
#include "ui_client.h"
#include "databaseaccessor.h"
Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    qDebug() << "QThread: " << QThread::currentThread();

    DatabaseThread* DB = new DatabaseThread();
    DB->setQuery("SELECT * from users");
    QVector<QVector<QVariant>> res = DB->getData();

    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size(); j++){
            qDebug() << res[i][j].toString();
        }
        qDebug() << "";
    }

}

Client::~Client()
{
    delete ui;
}

