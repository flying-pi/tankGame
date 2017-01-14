#include "maingameloop.h"
#include "mapiniter.h"
#include <QtGlobal>
#include <coreutil.h>
#include "diffs/simplediffcard.h"

QString TAG = "MainGameLoop";

MainGameLoop::MainGameLoop() {
  map = MapIniter().initSimapleMap();
  time = 1;
}
void MainGameLoop::proccessGamerMessage(MailReceiver::mailMessage* msg,
                                        MailSender* receiver) {
  GamerInformation* currentGamer = nullptr;
  bool isAlredyExist = false;
  for (int i = 0; i < gamersList.size(); i++) {
    if (gamersList.at(i)->sender == receiver) {
      isAlredyExist = true;
      currentGamer = gamersList.at(i);
      break;
    }
  }
  if (!isAlredyExist) {
    currentGamer->name = codingNum(gamersList.size());
    currentGamer->sender = receiver;
    gamersList.append(currentGamer);

    gamersItems.append(new QList<IBaseGameElement*>());

    BaseBasis* basis = new BaseBasis();
    basis->setPosition(&currentGamer->position);
    basis->setEnergy(currentGamer->lifeCount);
    map->insertElement(basis, basis->getPosition());

    gamersItems.last()->append(basis);
    currentGamer->minion = gamersItems.last();
    auto op = [](IBaseGameElement* element) -> bool {
      DiffElement* diff = new DiffElement(eDiffType::eNew, element);
      //      diff->time = this->time;
      //      currentGamer->personalDiff->append(diff);
      return false;
    };
    map->proccessAllInR(basis, basis->getRVision(), op);
    receiver->receiveResponce(currentGamer->personalDiff, msg->message);
  }
}

void MainGameLoop::proccessWatcherMessage(MailReceiver::mailMessage* msg,
                                          MailSender* receiver) {
  if (!watchers.contains(receiver))
    watchers.append(receiver);
  switch (msg->message->messageType) {
    case eFirstMessae:
      receiver->receiveResponce(getAllMapAsDiff(), msg->message);
      break;
    case eGetUpdateMessage:
      Q_ASSERT_X(2 * 2 != 4, "implementation", "not implemented yet");
      break;
    default:
      receiver->receiveResponce(new SimpleDiffCard(), msg->message);
  }
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
  qInfo() << "starting main loop";
  while (isWork) {
    while ((msg = nextMessage()) != nullptr) {
      qInfo() << TAG << "receive new messahe " << (*msg);
      auto fun = getProccessorForMessage(msg->message->connectionType);
      (this->*fun)(msg, msg->sender);
    }
    msleep(100);
  }
}

DiffCard* MainGameLoop::getAllMapAsDiff() {
  DiffCard* result = new SimpleDiffCard();
  DiffElement* item;
  for (int i = 0; i < map->getCount(); i++)
    result->append(
        new DiffElement(eDiffType::eNew, map->getElementAtPosition(i)));
  return result;
}

MainGameLoop::~MainGameLoop() {
  delete map;
  for (int i = 0; i < gamersItems.size(); i++) {
    delete gamersItems.at(i);
  }
}

void MainGameLoop::startLooper() {
  this->start();
}

MainGameLoop* MainGameLoop::instance = nullptr;

MainGameLoop::GamerInformation::GamerInformation(IMap* map) {
  name = "";
  lifeCount = limits::defaultBasisEnergy;
  QSizeF* size = map->getSize();
  float rand1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float rand2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  position = QVector3D(size->width() * rand1, size->height() * rand2, 0);

  personalDiff = new SimpleDiffCard();
}

MainGameLoop::GamerInformation::~GamerInformation() {
  delete personalDiff;
}
