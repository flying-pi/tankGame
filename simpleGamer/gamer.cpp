#include "gamer.h"
#include "GameElements/basetank.h"
#include <cmath>

Gamer::Gamer(QObject* parent)
    : QObject(parent), connection(QHostAddress::LocalHost, this) {}

void Gamer::startGamer() {
  connection.openConnection();
  connect(&connection, SIGNAL(onDiffReceive(QList<DiffElement*>*)), this,
          SLOT(onDiffReceive(QList<DiffElement*>*)));
  connection.getBulder()->asFirstMessage(eConnectionType::eGamer)->build();
}

void Gamer::onDiffReceive(QList<DiffElement*>* diffList) {
  //  if (count == 0) {
  //    this->basis =
  //    (BaseBasis*)diffList->at(0)->generateGameElementInstance();
  //  }
  if (count > 4)
    return;

  QList<IBaseGameElement*>* items = new QList<IBaseGameElement*>();
  for (int i = 0; i < 25; i++) {
    BaseTank* newElement = new BaseTank();
    //    newElement->setPosition(
    //        new QVector3D(basis->getPosition()->x(),
    //        basis->getPosition()->y(), 0));
    newElement->setPosition(new QVector3D(0, 0, 0));
    newElement->setDirection((double)rand() / (double)RAND_MAX * M_PI * 2);
    newElement->setSpeed(((double)rand() / (double)RAND_MAX) * 0.3 - 0.15);
    items->append(newElement);
  }
  connection.getBulder()->addNewItem(items)->build();

  count++;
}
