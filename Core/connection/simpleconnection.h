#ifndef SIMPLECONNECTION_H
#define SIMPLECONNECTION_H

#include <QHostAddress>
#include <QObject>
#include <QThread>
#include <QQueue>
#include <QTcpSocket>
#include <QDataStream>
#include <ibasegameelement.h>
#include "diffs/diffelement.h"
#include <QList>
#include "gameelementfactory.h"
#include <QMutex>


enum eConnectionType { eGamer, eWatcher };
enum eMessageType { eFirstMessae, eGetUpdateMessage, eInsertNewItem };

QString stringify(eConnectionType e);
QString stringify(eMessageType e);

class MessageForServer : public QObject {
  Q_OBJECT

 public:
  eConnectionType connectionType;
  eMessageType messageType;
  QList<IBaseGameElement*>* items;

  MessageForServer() { items = new QList<IBaseGameElement*>(); }

  ~MessageForServer() { delete items; }

  friend QDataStream& operator<<(QDataStream& stream,
                                 const MessageForServer& myclass) {
    int itemsSize = myclass.items->size();
    QDataStream& result = stream << ((int)myclass.connectionType)
                                 << ((int)myclass.messageType) << itemsSize;
    for (int i = 0; i < myclass.items->size(); i++)
      result << (*myclass.items->at(i));
    return result;
  }
  friend QDataStream& operator>>(QDataStream& stream,
                                 MessageForServer& myclass) {
    int con;
    int msg;
    int countOfNewItems = 0;
    QDataStream& result = (stream >> con >> msg >> countOfNewItems);
    myclass.connectionType = (eConnectionType)con;
    myclass.messageType = (eMessageType)msg;
    for (int i = 0; i < countOfNewItems; i++) {
      GameElementData item;
      item.defaultInit();
      result >> item;
      myclass.items->append(getElement(item));
    }
    return result;
  }

  friend QDebug operator<<(QDebug debug, MessageForServer& c) {
    QDebugStateSaver saver(debug);
    debug.nospace() << c.toString();

    return debug;
  }

  QString toString();
};

class SimpleConnection : public QThread {
  Q_OBJECT
 public:
  explicit SimpleConnection(QHostAddress adress, QObject* parent = 0);
  virtual ~SimpleConnection();
  void openConnection();
  void sendDiff(QList<DiffElement*>* diffs);

  class MessageBuilder {
    friend class SimpleConnection;

    MessageBuilder(SimpleConnection* sender);

   public:
    MessageBuilder* asFirstMessage(eConnectionType type);
    MessageBuilder* addNewItem(QList<IBaseGameElement*>* newEleements);
    MessageBuilder* updateWatcher();
    void build();

   private:
    MessageForServer* message;
    SimpleConnection* parent;
  };

  MessageBuilder* getBulder();

 signals:
  void onDiffReceive(QList<DiffElement*>* diffs);

 public slots:

 protected slots:
  void onSocketError(QAbstractSocket::SocketError error);
  void onReadyRead();

  // QThread interface
 protected:
  volatile bool isWork = true;
  void run() Q_DECL_OVERRIDE;
  QHostAddress adress;
  QTcpSocket* socket;

  QDataStream* out;

  QMutex mutex;
  QQueue<MessageForServer*> messages;

  void addMessage(MessageBuilder* messages);

  class ReceiverThread : public QThread {
   public:
    ReceiverThread(QTcpSocket* socket,
                   SimpleConnection* parentThread,
                   QObject* parent = 0) {
      this->socket = socket;
      this->parentThread = parentThread;
      in = new QDataStream(socket);
      in->setVersion(QDataStream::Qt_5_7);
    }

    virtual ~ReceiverThread() { delete in; }

    bool istThreadStart();
    void stop();

   protected:
    QTcpSocket* socket;
    QDataStream* in;
    SimpleConnection* parentThread;
    volatile bool isStart = false;
    volatile bool isWork = true;
    volatile bool isLoopActive = false;

    // QThread interface
   protected:
    void run() Q_DECL_OVERRIDE {
      qInfo() << "starting message receiver loop";

      int diffsLenth;
      MessageForServer sendedMessage;
      while (true) {
        isLoopActive = true;
        if (!isWork)
          break;
        isStart = true;
        bool waitForReadyReadResult = socket->waitForReadyRead(-1);

        qInfo() << "starting reading some response";
        (*in) >> sendedMessage;
        (*in) >> diffsLenth;
        QList<DiffElement*>* result = new QList<DiffElement*>();
        for (int i = 0; i < diffsLenth; i++) {
          DiffElement* newItem = new DiffElement();
          (*in) >> (*newItem);
          result->append(newItem);
        }
        parentThread->sendDiff(result);
        qInfo() << "something read from server";
      }
      isLoopActive = false;
    }
  };
  ReceiverThread* receiver;
};

#endif  // SIMPLECONNECTION_H
