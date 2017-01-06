#include "basetank.h"
#include <QDataStream>

BaseTank::BaseTank() {}

void BaseTank::setType(int value) {
  if (value != ((int)eSimpleTank)) {
    Q_ASSERT_X(false, "game logic", "Wrong type for tank");
  }
  IBaseGameElement::setType(value);
}

BaseBulet BaseTank::generateBullet() {}

void BaseTank::setAdditionakData(QByteArray* data) {
  IBaseGameElement::setAdditionakData(data);
  QDataStream stream(*data);
  stream >> direction >> speed >> fireType;
}

QByteArray* BaseTank::getAdditionalData() {
  this->additionalData->clear();
  QDataStream stream(this->additionalData, QIODevice::WriteOnly);
  stream << direction << speed << fireType;
  return additionalData;
}
