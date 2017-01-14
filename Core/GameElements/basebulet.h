#ifndef BASEBULET_H
#define BASEBULET_H

#include "../ibasegameelement.h"

class BaseBulet : public IBaseGameElement {
 public:
  BaseBulet();

 protected:
  int lifetime = 0;
  double demage = 0;
  double direction;
  double speed;

  // IBaseGameElement interface
 public:
  QByteArray* getAdditionalData();
  void setAdditionakData(QByteArray* data);
};

#endif  // BASEBULET_H