#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <core.h>
#include <QDebug>
#include <QTime>

#include "serverconnection.h"

void onServerError(serverError error){
qDebug() << "some bad error :: " << error;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    ServerConnection *server = ServerConnection::getInstance();
    QObject::connect(server,&ServerConnection::onServerError,&onServerError);
    server->startServer();
    return a.exec();
}
