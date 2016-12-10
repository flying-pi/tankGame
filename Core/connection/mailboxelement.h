#ifndef MAILBOXELEMENT_H
#define MAILBOXELEMENT_H

#include "simpleconnection.h"
#include "../ibasegameelement.h"
#include <QList>
#include <QMutex>
#include <QQueue>
#include <qtconcurrentrun.h>

using namespace QtConcurrent;

class MailReceiver;
class MailSender;

class MailReceiver {
 public:
  virtual void sendMail(MessageForServer* message,
                        MailSender* sender,
                        int type,
                        bool isReplace = true) {
    run(QThreadPool::globalInstance(), [=] {
      qInfo() << "MailReceiver::sendMail - befor mutex";
      isQueueLock = true;
      mutex.lock();
      qInfo() << "MailReceiver::sendMail - in mutex";
      qInfo() << "MailReceiver :: adding new message item in to queue";
      mailMessage* msg;
      if (isReplace && messages.length() != 0) {
        for (int i = 0; i < messages.length(); i++) {
          msg = messages.at(i);
          if ((msg->sender == sender && msg->type == type) ||
              i == messages.length() - 1) {
            messages.removeAt(i);
            messages.insert(i,
                            new mailMessage(message, sender, type, isReplace));
            break;
          }
        }
      } else
        messages.push_back(new mailMessage(message, sender, type, isReplace));
      mailMessage* test = messages.last();
      qInfo() << "getting new message in queue :: " << (*messages.last());
      mutex.unlock();
      isQueueLock = false;
      qInfo() << "MailReceiver::sendMail - after mutex";
    });
  }

 protected:
  class mailMessage {
   public:
    MessageForServer* message;
    MailSender* sender;
    int type;
    bool isReplace;
    mailMessage(MessageForServer* message,
                MailSender* sender,
                int type,
                bool isReplace = true) {
      this->message = message;
      this->sender = sender;
      this->type = type;
      this->isReplace = isReplace;
    }
    friend QDebug operator<<(QDebug debug, const mailMessage& c) {
      QDebugStateSaver saver(debug);

      if (c.message != nullptr) {
        debug.nospace() << "mailMessage {message:" << (*c.message) << "}";
      } else {
        debug.nospace() << "mailMessage {message:empty}";
      }

      return debug;
    }
  };
  QQueue<mailMessage*> messages;
  QMutex mutex;
  volatile bool isQueueLock = false;

  virtual mailMessage* nextMessage() {
    if (isQueueLock)
      return nullptr;
    mutex.lock();
    mailMessage* result = nullptr;
    if (messages.length() > 0) {
      qInfo() << "enqueue message";
      result = messages.takeFirst();
    }
    mutex.unlock();
    return result;
  }
};

class MailSender {
 public:
  virtual void receiveResponce(QList<DiffElement*>* diff,
                               MessageForServer* message) = 0;
  virtual void setDefaultReceiver(MailReceiver* receiver) {
    this->receiver = receiver;
  }

 protected:
  MailReceiver* receiver;
};

#endif  // MAILBOXELEMENT_H
