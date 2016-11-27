#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <core.h>
#include <QDebug>
#include <QTime>

#include "serverconnection.h"
#include "maingameloop.h"

void onServerError(serverError error) {
  qDebug() << "some bad error :: " << error;
}

void initMainLooper() {
  MainGameLoop* mainLooper = MainGameLoop::getLooperInstance();
  mainLooper->startLooper();
}

void initServer() {
  ServerConnection* server = ServerConnection::getServerInstance();
  QObject::connect(server, &ServerConnection::onServerError, &onServerError);
  server->setDefaultReceiver(MainGameLoop::getLooperInstance());
  server->startServer();
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  QTime midnight(0, 0, 0);
  qsrand(midnight.secsTo(QTime::currentTime()));

  initServer();

  return a.exec();
}
