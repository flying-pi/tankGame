#include "basebulet.h"

BaseBulet::BaseBulet() : IBaseGameElement() {
  this->type = eBullet;
}

BaseBulet::BaseBulet(GameElementData& data) : IBaseGameElement() {
  init(data);
  this->type = eBullet;
}

QByteArray* BaseBulet::getAdditionalData() const {}

void BaseBulet::setAdditionakData(QByteArray* data) {}
