#include "simpleconnection.h"
#include "../coreconst.h"
#include <QMetaEnum>

SimpleConnection::SimpleConnection(QHostAddress adress, QObject* parent)
    : QThread(parent) {
  this->adress = adress;
}

SimpleConnection::~SimpleConnection() {
  delete socket;
  delete out;
}

void SimpleConnection::openConnection() {
  this->start();
}

SimpleConnection::MessageBuilder* SimpleConnection::getBulder() {
  return new MessageBuilder(this);
}

void SimpleConnection::onSocketError(QAbstractSocket::SocketError err) {
  qCritical() << err;
  isWork = false;
  // TODO add something
}

void SimpleConnection::run() {
  socket = new QTcpSocket();
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(onSocketError(QAbstractSocket::SocketError)),
          Qt::DirectConnection);
  socket->connectToHost(adress, DefaultServerParams::port);
  isWork = socket->waitForConnected();
  qDebug() << "Connect to server on " << socket->peerAddress().toString() << ":"
           << socket->peerPort();
  out = new QDataStream();
  out->setDevice(socket);
  out->setVersion(QDataStream::Qt_5_7);

  in = new QDataStream();
  in->setDevice(socket);
  in->setVersion(QDataStream::Qt_5_7);

  while (isWork) {
    if (messages.length() > 0) {
      MessageForServer* newMessage = messages.takeFirst();
      out->startTransaction();
      (*out) << (*newMessage);
      out->commitTransaction();
      socket->flush();
      continue;
    }
    bool isEnethinRead = false;
    while (socket->waitForReadyRead(10000)) {
      qInfo() << "something read from server";
      isEnethinRead = true;
      MessageForServer sendedMessage;
      (*in) >> sendedMessage;
      int diffsLenth;
      (*in) >> diffsLenth;
      QList<DiffElement*>* result = new QList<DiffElement*>();
      for (int i = 0; i < diffsLenth; i++) {
        DiffElement* newItem = new DiffElement();
        (*in) >> (*newItem);
        result->append(newItem);
      }
      emit onDiffReceive(result);
    }
    if (!isEnethinRead)
      msleep(100);
  }
}

void SimpleConnection::addMessage(MessageBuilder* message) {
  mutex.lock();
  this->messages.push_back(message->message);
  delete message;
  mutex.unlock();
}

SimpleConnection::MessageBuilder::MessageBuilder(SimpleConnection* sender) {
  this->parent = sender;
  this->message = new MessageForServer();
}

SimpleConnection::MessageBuilder*
SimpleConnection::MessageBuilder::asFirstMessage(eConnectionType type) {
  this->message->connectionType = type;
  this->message->messageType = eFirstMessae;
  return this;
}

void SimpleConnection::MessageBuilder::build() {
  parent->addMessage(this);
}

QString MessageForServer::toString() {
  return "MessageForServer :: connectionType = " + stringify(connectionType) +
         "; messageType = " + stringify(messageType);
}

QString stringify(eConnectionType e) {
  switch (e) {
    case eGamer:
      return "eGamer";
    case eWatcher:
      return "eWatcher";
  }
  return "";
}

QString stringify(eMessageType e) {
  switch (e) {
    case eFirstMessae:
      return "eFirstMessae";
    case eGetUpdateMessage:
      return "eGetUpdateMessage";
  }
  return "";
}
