#include "maingameloop.h"
#include "mapiniter.h"
#include <QtGlobal>
#include <coreutil.h>
#include "diffs/simplediffcard.h"
#include <cmath>

QString TAG = "MainGameLoop";

MainGameLoop::MainGameLoop() {
  map = MapIniter().initSimapleMap();
  time = 1;
  stepDiff = getSimpleDiff();
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
    currentGamer = new GamerInformation(map);
    currentGamer->name = codingNum(gamersList.size());
    currentGamer->sender = receiver;
    gamersList.append(currentGamer);

    gamersItems.append(new QList<IBaseGameElement*>());

    BaseBasis* basis = new BaseBasis();
    basis->setPosition(&currentGamer->position);
    basis->setEnergy(currentGamer->lifeCount);
    currentGamer->personalDiff->append(new DiffElement(eDiffType::eNew, basis));

    map->insertElement(basis);
    gamersItems.last()->append(basis);

    currentGamer->minion = gamersItems.last();
    auto op = [this, currentGamer](IBaseGameElement* element) -> bool {
      DiffElement* diff = new DiffElement(eDiffType::eNew, element);
      diff->time = this->time;
      currentGamer->personalDiff->append(diff);
      return false;
    };
    map->proccessAllInR(basis, basis->getRVision(), op);
  } else {
    if (msg->message->messageType == eInsertNewItem) {
      for (int i = 0; i < msg->message->items->size(); i++) {
        map->insertElement(msg->message->items->at(i));
        currentGamer->minion->append(msg->message->items->at(i));
        DiffElement* diffItem =
            new DiffElement(eDiffType::eNew, msg->message->items->at(i));
        diffItem->time = time;
        stepDiff->append(diffItem);
      }
    }
  }
  auto diffValue = currentGamer->personalDiff;
  currentGamer->personalDiff = getSimpleDiff();
  receiver->receiveResponce(diffValue, msg->message);
}

void MainGameLoop::proccessWatcherMessage(MailReceiver::mailMessage* msg,
                                          MailSender* receiver) {
  WathcerInformation* watcher = nullptr;
  for (int i = 0; i < watchers.size() && watcher == nullptr; i++) {
    if (watchers.at(i)->sender == receiver)
      watcher = watchers.at(i);
  }
  if (watcher == nullptr) {
    watcher = new WathcerInformation();
    watcher->sender = receiver;
    watchers.append(watcher);
  }
  switch (msg->message->messageType) {
    case eFirstMessae:
      receiver->receiveResponce(getAllMapAsDiff(), msg->message);
      break;
    case eGetUpdateMessage:
      receiver->receiveResponce(watcher->personalDiff, msg->message);
      watcher->personalDiff = getSimpleDiff();
      //      receiver->receiveResponce(getAllMapAsDiff(), msg->message);
      break;
    default:
      receiver->receiveResponce(getSimpleDiff(), msg->message);
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
    // process incoming messages
    while ((msg = nextMessage()) != nullptr) {
      qInfo() << TAG << "receive new messahe " << (*msg);
      auto fun = getProccessorForMessage(msg->message->connectionType);
      (this->*fun)(msg, msg->sender);
    }

    for (int g = 0; g < gamersItems.size(); g++) {
      auto items = gamersItems.at(g);
      for (int i = 0; i < items->size(); i++) {
        switch ((eBaseGameElementType)items->at(i)->getType()) {
          case eGrass:
            break;
          case eSimpleTank: {
            BaseTank* tank = (BaseTank*)items->at(i);
            auto pos = tank->getPosition();
            pos->setX(pos->x() + cos(tank->getDirection()) * tank->getSpeed());
            pos->setY(pos->y() + sin(tank->getDirection()) * tank->getSpeed());
            tank->setPosition(pos);
            tank->setDirection(
                (((double)rand() / (double)RAND_MAX) * 0.02 - 0.01) +
                tank->getDirection());
            auto diff = new DiffElement(eDiffType::eChange, tank, time);
            stepDiff->append(diff);
            gamersList.at(g)->personalDiff->append(new DiffElement(*diff));
          } break;
          case eBasis:
            break;
          case eBullet:
            break;
        }
      }
    }
    for (int i = 0; i < watchers.size(); i++) {
      WathcerInformation* watcher = watchers.at(i);
      watcher->personalDiff->updateFromOtherCard(stepDiff);
    }
    stepDiff->freeItems();

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
  float rand1 = ((float)(rand())) / ((float)(RAND_MAX));
  float rand2 = ((float)(rand())) / ((float)(RAND_MAX));
  position = QVector3D(size->width() * rand1, size->height() * rand2, 0);
  personalDiff = getSimpleDiff();
}

MainGameLoop::GamerInformation::~GamerInformation() {
  delete personalDiff;
}

DiffCard* getSimpleDiff() {
  return new SimpleDiffCard();
}
