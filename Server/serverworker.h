#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QTcpSocket>
#include <QThread>
#include <QDataStream>

#include <connection/mailboxelement.h>

class ServerWorker : public QThread, public MailSender {
 public:
  ServerWorker(QTcpSocket* socket);

  // QThread interface
 protected:
  void run();

 protected:
  struct responceData {
   public:
    responceData(QList<DiffElement*>* diff, MessageForServer* messag) {
      this->diff = diff;
      this->messag = messag;
    }

    QList<DiffElement*>* diff;
    MessageForServer* messag;
  };

  QTcpSocket* socket;
  volatile bool isWork = true;
  QDataStream* in;
  QDataStream* out;
  QMutex workerMutex;
  QQueue<responceData> responceMessage;

  // MailSender interface
 public:
  void receiveResponce(QList<DiffElement*>* diff, MessageForServer* message);
};

#endif  // SERVERWORKER_H
