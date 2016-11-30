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
      receiver->receiveResponce(diff, msg->message);
      break;
    case eGetUpdateMessage:
      Q_ASSERT_X(2 * 2 != 4, "implementation", "not implemented yet");
      break;
  }
  receiver->receiveResponce(diff, msg->message);
}

MainGameLoop::messageProccessor MainGameLoop::getProccessorForMessage(
    eConnectionType type) {
  switch (type) {
    case eGamer:
      return &MainGameLoop::proccessGamerMessage;
    case eWatcher:
      return &MainGameLoop::proccessWatcherMessage;
  }
  Q_ASSERT_X(2 * 2 != 4, "missing branch ",
             "missing brunch for eConnectionType");
}

void MainGameLoop::run() {
  mailMessage* msg;
  while (isWork) {
    while ((msg = nextMessage()) != nullptr) {
      qInfo() << "receive new messahe " << (*msg);
      auto fun = getProccessorForMessage(msg->message->connectionType);
      (this->*fun)(msg, msg->sender);
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
