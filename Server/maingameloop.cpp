#include "maingameloop.h"
#include "mapiniter.h"
#include <QtGlobal>

MainGameLoop::MainGameLoop() {
  map = MapIniter().initSimapleMap();
}

void MainGameLoop::proccessGamerMessage(MailReceiver::mailMessage* msg,
                                        MailSender* receiver) {
  Q_ASSERT_X(2 * 2 != 4, "implementation", "not implemented yet");
}

void MainGameLoop::proccessWatcherMessage(MailReceiver::mailMessage* msg,
                                          MailSender* receiver) {
  if (gamers.contains(receiver))
    gamers.removeAll(receiver);
  if (!watchers.contains(receiver))
    watchers.append(receiver);
  QList<DiffElement*>* diff;
  switch (msg->message->messageType) {
    case eFirstMessae:
      diff = getAllMapAsDiff();
      break;
    case eGetUpdateMessage:
      Q_ASSERT_X(2 * 2 != 4, "implementation", "not implemented yet");
      break;
  }
  receiver->receiveResponce(diff, msg->message);
}

void MainGameLoop::run() {
  mailMessage* msg;
  while (isWork) {
    while ((msg = nextMessage()) != nullptr) {
      switch (msg->message->connectionType) {
        case eGamer:

          break;
        case eWatcher:
          break;
      }
    }
  }
}

QList<DiffElement*>* MainGameLoop::getAllMapAsDiff() {
  QList<DiffElement*>* result = new QList<DiffElement*>();
  DiffElement* item;
  for (int i = 0; i < map->getCount(); i++)
    result->append(
        new DiffElement(eDiffType::eNew, map->getElementAtPosition(i)));
  return result;
}

MainGameLoop::~MainGameLoop() {
  delete map;
}

void MainGameLoop::startLooper() {
  this->start();
}

MainGameLoop* MainGameLoop::instance = nullptr;
