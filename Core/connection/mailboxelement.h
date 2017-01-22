#ifndef MAILBOXELEMENT_H
#define MAILBOXELEMENT_H

#include "simpleconnection.h"
#include "../ibasegameelement.h"
#include <QList>
#include <QMutex>
#include <QQueue>
#include <qtconcurrentrun.h>
#include "diffs/diffcard.h"

using namespace QtConcurrent;

class MailReceiver;
class MailSender;

class MailReceiver {
 public:
  MailReceiver();
  ~MailReceiver();
  virtual void sendMail(MessageForServer* message,
                        MailSender* sender,
                        int type,
                        bool isReplace = true);

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
                bool isReplace = true);
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
  QMutex* mutex;

  virtual mailMessage* nextMessage();
};

class MailSender {
 public:
  virtual void receiveResponce(DiffCard* diff, MessageForServer* message) = 0;
  virtual void setDefaultReceiver(MailReceiver* receiver) {
    this->receiver = receiver;
  }

 protected:
  MailReceiver* receiver;
};

#endif  // MAILBOXELEMENT_H
