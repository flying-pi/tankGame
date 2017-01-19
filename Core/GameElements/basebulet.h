#ifndef BASEBULET_H
#define BASEBULET_H

#include "../ibasegameelement.h"

class BaseBulet : public IBaseGameElement {
 public:
  BaseBulet();
  BaseBulet(GameElementData& data);

 protected:
  int lifetime = 0;
  double demage = 0;
  double direction;
  double speed;

  // IBaseGameElement interface
 public:
  QByteArray* getAdditionalData() const;
  using IBaseGameElement::setAdditionakData;
  void setAdditionakData(QByteArray* data) override;
};

#endif  // BASEBULET_H
