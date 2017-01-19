#include "basebulet.h"

BaseBulet::BaseBulet() : IBaseGameElement() {
  this->type = eBullet;
}

BaseBulet::BaseBulet(GameElementData& data) {
  init(data);
  this->type = eBullet;
}

QByteArray* BaseBulet::getAdditionalData() const {}

void BaseBulet::setAdditionakData(QByteArray* data) {}
