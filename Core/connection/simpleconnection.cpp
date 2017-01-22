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
  socket = new QTcpSocket();
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(onSocketError(QAbstractSocket::SocketError)),
          Qt::DirectConnection);
  connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()),
          Qt::DirectConnection);
  out = new QDataStream();
  out->setDevice(socket);
  out->setVersion(QDataStream::Qt_5_7);
  receiver = new ReceiverThread(socket, this);
  receiver->start();
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

void SimpleConnection::onReadyRead() {
  qInfo() << "onReadyRead";
}

void SimpleConnection::run() {
  socket->connectToHost(adress, DefaultServerParams::port);
  isWork = socket->waitForConnected();
  qDebug() << "Connect to server on " << socket->peerAddress().toString() << ":"
           << socket->peerPort();

  while (!receiver->istThreadStart())
    qInfo() << "whaiting for receiver loop start........";

  qInfo() << "starting sending to server message loop";
  while (isWork) {
    if (messages.length() > 0) {
      MessageForServer* newMessage = messages.takeFirst();
      out->startTransaction();
      (*out) << (*newMessage);
      out->commitTransaction();
      socket->flush();
      qInfo() << "sending some message for server";
      continue;
    } else {
      msleep(100);
    }
  }
  receiver->stop();
  delete receiver;
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

SimpleConnection::MessageBuilder* SimpleConnection::MessageBuilder::addNewItem(
    QList<IBaseGameElement*>* newEleements) {
  this->message->connectionType = eConnectionType::eGamer;
  this->message->messageType = eInsertNewItem;
  this->message->items->append(*newEleements);
  return this;
}

SimpleConnection::MessageBuilder*
SimpleConnection::MessageBuilder::updateWatcher() {
  this->message->connectionType = eConnectionType::eWatcher;
  this->message->messageType = eGetUpdateMessage;
  return this;
}

void SimpleConnection::MessageBuilder::build() {
  parent->addMessage(this);
}

void SimpleConnection::sendDiff(QList<DiffElement*>* diffs) {
  emit onDiffReceive(diffs);
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

bool SimpleConnection::ReceiverThread::istThreadStart() {
  return isStart;
  msleep(100);
}

void SimpleConnection::ReceiverThread::stop() {
  isWork = false;
  while (isLoopActive) {
    msleep(100);
  }
}
