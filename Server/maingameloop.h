#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include "imap.h"
#include "connection/mailboxelement.h"
#include <QThread>
#include <functional>
#include "GameElements/basetank.h"
#include "coreconst.h"
#include "GameElements/basebasis.h"
#include "diffs/diffcard.h"

// clever clean, whait for stop all thread

// clean diffs

DiffCard* getGamerDiff();

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

 protected:
  class GamerInformation {
   public:
    QString name;
    uint64_t lifeCount;
    QVector3D position;
    MailSender* sender;
    QList<IBaseGameElement*>* minion;
    DiffCard* personalDiff;
    GamerInformation(IMap* map);
    ~GamerInformation();
  };

  class WathcerInformation {
   public:
    MailSender* sender;
    WathcerInformation() {}
  };

  void run();
  bool isWork = true;
  DiffCard* getAllMapAsDiff();
  QList<DiffElement*>* getInitDiffsForGamer(BaseBasis* basis);
  QList<MailSender*> watchers;
  /**
   * list of client as gamers
   * @brief gamersList
   */
  QList<GamerInformation*> gamersList;
  /**
   * list of gamer object; Each list represent game element of each gamer;
   * firs element of each gamer object is basis
   * @brief gamersItems
   */
  QList<QList<IBaseGameElement*>*> gamersItems;

  uint64_t time;
};

#endif  // MAINGAMELOOP_H
