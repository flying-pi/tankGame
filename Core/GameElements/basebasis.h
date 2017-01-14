#ifndef BASEBASIS_H
#define BASEBASIS_H

#include "../ibasegameelement.h"

class BaseBasis : public IBaseGameElement {
 public:
  BaseBasis();
  virtual void setType(int value) override;
  virtual QByteArray* getAdditionalData();
  virtual void setAdditionakData(QByteArray* data);

  virtual int getEnergy() { return energy; }
  virtual void setEnergy(int _enery) { this->energy = _enery; }

 protected:
  int energy = 100;
};

#endif  // BASEBASIS_H
