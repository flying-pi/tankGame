#include "basebulet.h"

BaseBulet::BaseBulet() : IBaseGameElement() {
  this->type = eBullet;
}

QByteArray* BaseBulet::getAdditionalData() {}

void BaseBulet::setAdditionakData(QByteArray* data) {}
