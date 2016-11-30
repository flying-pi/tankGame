#ifndef SIMPLECONNECTION_H
#define SIMPLECONNECTION_H

#include <QHostAddress>
#include <QObject>
#include <QThread>
#include <QQueue>
#include <QTcpSocket>
#include <QDataStream>
#include <ibasegameelement.h>

enum eConnectionType { eGamer, eWatcher };
enum eMessageType { eFirstMessae, eGetUpdateMessage };

QString stringify(eConnectionType e);
QString stringify(eMessageType e);

class MessageForServer : public QObject {
  Q_OBJECT

 public:
  eConnectionType connectionType;
  eMessageType messageType;

  friend QDataStream& operator<<(QDataStream& stream,
                                 const MessageForServer& myclass) {
    return stream << ((int)myclass.connectionType)
                  << ((int)myclass.messageType);
  }
  friend QDataStream& operator>>(QDataStream& stream,
                                 MessageForServer& myclass) {
    int con;
    int msg;
    QDataStream& result = (stream >> con >> msg);
    myclass.connectionType = (eConnectionType)con;
    myclass.messageType = (eMessageType)msg;
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

  class MessageBuilder {
    friend class SimpleConnection;

    MessageBuilder(SimpleConnection* sender);

   public:
    MessageBuilder* asFirstMessage(eConnectionType type);
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

  // QThread interface
 protected:
  volatile bool isWork = true;
  void run();
  QHostAddress adress;
  QTcpSocket* socket;

  QDataStream* out;
  QDataStream* in;

  QMutex mutex;
  QQueue<MessageForServer*> messages;

  void addMessage(MessageBuilder* messages);
};

#endif  // SIMPLECONNECTION_H
