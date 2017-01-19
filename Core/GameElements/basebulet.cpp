#include "basebulet.h"

BaseBulet::BaseBulet() : IBaseGameElement() {
  this->type = eBullet;
}

BaseBulet::BaseBulet(GameElementData& data) : IBaseGameElement(data) {
  this->type = eBullet;
}

QByteArray* BaseBulet::getAdditionalData() {}

void BaseBulet::setAdditionakData(QByteArray* data) {}
