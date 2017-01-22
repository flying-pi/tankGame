#include "mailboxelement.h"

MailReceiver::MailReceiver() {
  mutex = new QMutex();
}

MailReceiver::~MailReceiver() {
  delete mutex;
}

void MailReceiver::sendMail(MessageForServer* message,
                            MailSender* sender,
                            int type,
                            bool isReplace) {
  run(QThreadPool::globalInstance(), [=] {
    qInfo() << "MailReceiver::sendMail - befor mutex";
    mutex->lock();
    qInfo() << "MailReceiver::sendMail - in mutex";
    qInfo() << "MailReceiver :: adding new message item in to queue";
    mailMessage* msg;
    if (isReplace && messages.length() != 0) {
      for (int i = 0; i < messages.length(); i++) {
        msg = messages.at(i);
        if (msg->sender == sender && msg->type == type) {
          messages.removeAt(i);
          messages.insert(i, new mailMessage(message, sender, type, isReplace));
          break;
        }
        if (i == messages.length() - 1) {
          messages.push_back(new mailMessage(message, sender, type, isReplace));
        }
      }
    } else
      messages.push_back(new mailMessage(message, sender, type, isReplace));
    mailMessage* test = messages.last();
    qInfo() << "getting new message in queue :: " << (*messages.last());
    mutex->unlock();
    qInfo() << "MailReceiver::sendMail - after mutex";
  });
}

MailReceiver::mailMessage* MailReceiver::nextMessage() {
  mutex->lock();
  mailMessage* result = nullptr;
  if (messages.length() > 0) {
    qInfo() << "enqueue message";
    result = messages.takeFirst();
  }
  mutex->unlock();
  return result;
}

MailReceiver::mailMessage::mailMessage(MessageForServer* message,
                                       MailSender* sender,
                                       int type,
                                       bool isReplace) {
  this->message = message;
  this->sender = sender;
  this->type = type;
  this->isReplace = isReplace;
}
