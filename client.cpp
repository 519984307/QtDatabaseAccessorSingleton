#include "client.h"
#include "ui_client.h"
#include "databaseaccessor.h"
Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    DatabaseThread* DB = new DatabaseThread();
}

Client::~Client()
{
    delete ui;
}

