#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QThread>
#include <QTcpServer>
#include <QList>
#include "serverworker.h"
#include "connection/mailboxelement.h"

enum serverError { canNotStartServer };

class ServerConnection : public QThread, public MailSender {
 public:
  Q_OBJECT

 public:
  ~ServerConnection();
  inline static ServerConnection* getServerInstance() {
    if (instance == nullptr)
      instance = new ServerConnection();
    return instance;
  }
  void startServer();

 signals:
  void onServerError(serverError error);

 private:
  static ServerConnection* instance;
  ServerConnection();
  QTcpServer* server;
  QList<ServerWorker*>* connections;

  // QThread interface
 protected:
  void run();

  // MailSender interface
 public:
  void receiveResponce(QList<DiffElement*>* diff, MessageForServer* message);
};

#endif  // SERVERCONNECTION_H
