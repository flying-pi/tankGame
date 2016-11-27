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
    run(QThreadPool::globalInstance(), [&] {
      mutex.lock();
      mailMessage* msg;
      if (isReplace) {
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
      mutex.unlock();
    });
  }

 protected:
  struct mailMessage {
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
  };
  QQueue<mailMessage*> messages;
  QMutex mutex;

  mailMessage* nextMessage() {
    if (!mutex.tryLock())
      return nullptr;
    mailMessage* result = nullptr;
    if (messages.length() > 0)
      result = messages.takeFirst();
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
