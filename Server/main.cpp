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
  qSetMessagePattern(
      "%{time boot} :: [%{type}::%{appname} in %{file}:%{line} th:%{threadid}] "
      "message:: "
      "%{message} "
      "%{backtrace [separator=\"\n\t\"]}");

  QTime midnight(0, 0, 0);
  qsrand(midnight.secsTo(QTime::currentTime()));

  initMainLooper();

  initServer();

  return a.exec();
}
