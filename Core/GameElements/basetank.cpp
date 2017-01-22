#include "basetank.h"
#include <QDataStream>

BaseTank::BaseTank() : IBaseGameElement() {
  this->type = eSimpleTank;
}

BaseTank::BaseTank(GameElementData& data) : IBaseGameElement() {
  init(data);
  this->type = eSimpleTank;
}

void BaseTank::setType(int value) {
  if (value != ((int)eSimpleTank)) {
    Q_ASSERT_X(false, "game logic", "Wrong type for tank");
  }
  IBaseGameElement::setType(value);
}


void BaseTank::setAdditionakData(QByteArray* data) {
  IBaseGameElement::setAdditionakData(data);
  QDataStream stream(*data);
  stream >> direction >> speed >> fireType;
}

QByteArray* BaseTank::getAdditionalData() const {
  this->additionalData->clear();
  QDataStream stream(this->additionalData, QIODevice::WriteOnly);
  stream << direction << speed << fireType;
  return additionalData;
}

void BaseTank::setDirection(double _direction) {
  direction = _direction;
  getAdditionalData();
}

void BaseTank::setSpeed(double _speed) {
  speed = _speed;
  getAdditionalData();
}
