#include "gamer.h"
#include "GameElements/basetank.h"

Gamer::Gamer(QObject* parent)
    : QObject(parent), connection(QHostAddress::LocalHost, this) {}

void Gamer::startGamer() {
  connection.openConnection();
  connect(&connection, SIGNAL(onDiffReceive(QList<DiffElement*>*)), this,
          SLOT(onDiffReceive(QList<DiffElement*>*)));
  connection.getBulder()->asFirstMessage(eConnectionType::eGamer)->build();
}

void Gamer::onDiffReceive(QList<DiffElement*>* diffList) {
  if (count > 10)
    return;
  BaseTank* newElement = new BaseTank();
  newElement->setPosition(new QVector3D(0, 0, 0));
  newElement->setDirection(0.2);
  newElement->setSpeed(10);
  QList<IBaseGameElement*>* items = new QList<IBaseGameElement*>();
  items->append(newElement);
  connection.getBulder()->addNewItem(items)->build();
  count++;
}
