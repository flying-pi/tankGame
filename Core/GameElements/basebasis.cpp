#include "basebasis.h"
#include <QDataStream>

BaseBasis::BaseBasis() : IBaseGameElement() {
  helth = InfinityDouble::InfinityValue();
  weight = InfinityDouble::InfinityValue();
  transitWeight = InfinityDouble::InfinityValue();
}

void BaseBasis::setType(int value) {
  if (value != ((int)eBasis)) {
    Q_ASSERT_X(false, "game logic", "Wrong type for basis");
  }
  IBaseGameElement::setType(value);
}

QByteArray* BaseBasis::getAdditionalData() {
  additionalData->clear();
  QDataStream stream(additionalData, QIODevice::WriteOnly);
  stream << energy;
}

void BaseBasis::setAdditionakData(QByteArray* data) {
  QDataStream stream(*data);
  stream >> energy;
  IBaseGameElement::setAdditionakData(data);
}
