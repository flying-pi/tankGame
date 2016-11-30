#include "serverworker.h"

#include <connection/simpleconnection.h>

ServerWorker::ServerWorker(QTcpSocket* socket) {
  this->socket = socket;
}

void ServerWorker::run() {
  in = new QDataStream(socket);
  in->setVersion(QDataStream::Qt_5_7);

  out = new QDataStream(socket);
  out->setVersion(QDataStream::Qt_5_7);

  while (this->isWork) {
    while (socket->waitForReadyRead(1)) {
      MessageForServer* newMessage = new MessageForServer();
      (*in) >> (*newMessage);
      qInfo() << "get new message on server :: " << (*newMessage).toString();
      receiver->sendMail(newMessage, this, newMessage->messageType);
    }
    while (responceMessage.length() > 0) {
      responceData data = responceMessage.takeFirst();
      out->startTransaction();
      (*out) << (*data.messag);
      (*out) << data.diff->length();
      for (int i = 0; i < data.diff->length(); i++)
        (*out) << (*data.diff->at(i));
      out->commitTransaction();
      socket->flush();
      for (int i = 0; i < data.diff->length(); i++) {
        delete data.diff->at(i);
      }
      delete data.diff;
      delete data.messag;
    }
  }
}

void ServerWorker::receiveResponce(QList<DiffElement*>* diff,
                                   MessageForServer* message) {
  QtConcurrent::run(QThreadPool::globalInstance(), [=] {
    workerMutex.lock();
    responceMessage.push_back(responceData(diff, message));
    workerMutex.unlock();
  });
}
