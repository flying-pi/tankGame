#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include "imap.h"
#include "connection/mailboxelement.h"
#include <QThread>
#include <functional>

class MainGameLoop : public MailReceiver, public QThread {
 public:
  ~MainGameLoop();
  inline static MainGameLoop* getLooperInstance() {
    if (instance == nullptr) {
      instance = new MainGameLoop();
    }
    return instance;
  }

  void startLooper();

 private:
  typedef void (MainGameLoop::*messageProccessor)(MailReceiver::mailMessage*,
                                                  MailSender*);
  static MainGameLoop* instance;
  IMap* map;
  MainGameLoop();

  void proccessGamerMessage(mailMessage* msg, MailSender* receiver);
  void proccessWatcherMessage(mailMessage* msg, MailSender* receiver);
  messageProccessor getProccessorForMessage(eConnectionType type);

  // QThread interface
 protected:
  void run();
  bool isWork;
  QList<DiffElement*>* getAllMapAsDiff();
  QList<MailSender*> watchers;
  QList<MailSender*> gamers;
};

#endif  // MAINGAMELOOP_H