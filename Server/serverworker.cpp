#include "serverworker.h"

#include <connection/simpleconnection.h>

ServerWorker::ServerWorker(QTcpSocket* socket) {
  this->socket = socket;
}

void ServerWorker::run() {
  out = new QDataStream(socket);
  out->setVersion(QDataStream::Qt_5_7);

  ReceiverThread* th = new ReceiverThread(this, socket);

  while (this->isWork) {
    workerMutex.lock();
    //    qInfo() << "responce messages list size :: " +
    //                   QString::number(responceMessage.length());
    while (responceMessage.length() > 0) {
      responceData data = responceMessage.takeFirst();
      qInfo() << "getting some message for sending";
      out->startTransaction();
      (*out) << (*data.messag);
      (*out) << data.diff->length();
      for (int i = 0; i < data.diff->length(); i++)
        (*out) << (*data.diff->at(i));
      out->commitTransaction();
      socket->flush();
      qInfo() << "send  response to client";
      for (int i = 0; i < data.diff->length(); i++) {
        delete data.diff->at(i);
        data.diff->removeAt(i);
        i--;
      }
      delete data.diff;
      delete data.messag;
    }
    workerMutex.unlock();
  }
  th->stop();
  delete th;
  qInfo() << "worker has stoped";
  emit onStop(this);
}

void ServerWorker::receiveResponce(QList<DiffElement*>* diff,
                                   MessageForServer* message) {
  qInfo() << "getting responce for client from map loop";
  QtConcurrent::run(QThreadPool::globalInstance(), [=] {
    workerMutex.lock();
    responceMessage.push_back(responceData(diff, message));
    workerMutex.unlock();
  });
}

ServerWorker::ReceiverThread::ReceiverThread(ServerWorker* parent,
                                             QTcpSocket* socket) {
  this->socket = socket;
  this->parentThread = parent;
  this->start();
}

ServerWorker::ReceiverThread::~ReceiverThread() {
  delete in;
}

void ServerWorker::ReceiverThread::stop() {
  receiverMutex.lock();
  isWork = false;
  receiverMutex.unlock();
}

void ServerWorker::ReceiverThread::run() {
  in = new QDataStream(socket);
  in->setVersion(QDataStream::Qt_5_7);

  qInfo() << "starting receiving thread";

  while (true) {
    receiverMutex.lock();
    socket->waitForReadyRead(-1);
    if (socket->state() == QTcpSocket::UnconnectedState ||
        socket->state() == QAbstractSocket::ClosingState)
      isWork = false;
    if (!isWork) {
      qInfo() << "stoping receiver loop";
      break;
    }
    qInfo() << "ready read from client";
    MessageForServer* newMessage = new MessageForServer();
    (*in) >> (*newMessage);
    qInfo() << "get new message on server :: " << (*newMessage).toString();
    parentThread->receiver->sendMail(newMessage, parentThread,
                                     newMessage->messageType);
    receiverMutex.unlock();
  }
}
