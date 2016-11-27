#include "serverconnection.h"
#include "coreconst.h"

ServerConnection* ServerConnection::instance = nullptr;

ServerConnection::~ServerConnection() {
  for (int i = 0; i < connections->size(); i++)
    delete connections->at(i);
  delete connections;
}

ServerConnection::ServerConnection() {
  connections = new QList<ServerWorker*>();
}

void ServerConnection::startServer() {
  if (this->isRunning())
    return;
  this->start(Priority::NormalPriority);
}

void ServerConnection::run() {
  server = new QTcpServer();
  if (!server->listen(QHostAddress::Any, DefaultServerParams::port)) {
    emit onServerError(serverError::canNotStartServer);
    return;
  }
  qDebug() << server->isListening();
  bool isAppareNewConnection;
  while (true) {
    isAppareNewConnection = server->waitForNewConnection(100);
    if (isAppareNewConnection) {
      QTcpSocket* newConnection = server->nextPendingConnection();
      if (newConnection == nullptr)
        continue;
      qInfo() << "appare new connection  :: "
              << newConnection->peerAddress().toString();
      ServerWorker* newWorker = new ServerWorker(newConnection);
      newWorker->setDefaultReceiver(this->receiver);
      connections->append(newWorker);
      newWorker->start();
    }
  }
}

void ServerConnection::receiveResponce(QList<DiffElement*>* diff,
                                       MessageForServer* message) {}
