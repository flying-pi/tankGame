#include "serverconnection.h"
#include "coreconst.h"


ServerConnection *ServerConnection::instance = nullptr;

ServerConnection::~ServerConnection()
{
    for(int i=0;i<connections->size();i++)
        delete connections->at(i);
    delete connections;
}

ServerConnection::ServerConnection()
{
    connections = new QList<ServerWorker *>();
}

void ServerConnection::startServer()
{
    if(this->isRunning())
        return;
    this->start(Priority::NormalPriority);
}

void ServerConnection::run()
{
    server = new QTcpServer();
    qDebug() << server->isListening();
    if(!server->listen(QHostAddress::Any,DefaultServerParams::port)){
        emit onServerError(serverError::canNotStartServer);
        return;
    }
    while (true) {
        QTcpSocket *newConnection = server->nextPendingConnection();
        qInfo() << "appare new connection  :: " << newConnection->localAddress();
        ServerWorker *newWorker = new ServerWorker(newConnection);
        connections->append(newWorker);
        newWorker->start();
    }

}

