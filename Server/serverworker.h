#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QTcpSocket>
#include <QThread>
#include <QDataStream>

#include <connection/mailboxelement.h>

class ServerWorker : public QThread, public MailSender {
  Q_OBJECT
 public:
  ServerWorker(QTcpSocket* socket);
 signals:
  void onStop(ServerWorker* worker);

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
  QDataStream* out;
  QMutex workerMutex;
  QQueue<responceData> responceMessage;

  class ReceiverThread : public QThread {
   public:
    ReceiverThread(ServerWorker* parent, QTcpSocket* socket);
    virtual ~ReceiverThread();
    void stop();

    // QThread interface
   protected:
    void run();
    QTcpSocket* socket;
    ServerWorker* parentThread;
    QDataStream* in;
    bool isWork = true;
    QMutex receiverMutex;
  };

  // MailSender interface
 public:
  void receiveResponce(QList<DiffElement*>* diff, MessageForServer* message);
};

#endif  // SERVERWORKER_H
