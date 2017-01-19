#ifndef BASEBASIS_H
#define BASEBASIS_H

#include "../ibasegameelement.h"

class BaseBasis : public IBaseGameElement {
 public:
  BaseBasis();
  BaseBasis(GameElementData& data);
  using IBaseGameElement::getType;
  virtual void setType(int value) override;
  virtual QByteArray* getAdditionalData() const;
  using IBaseGameElement::setAdditionakData;
  virtual void setAdditionakData(QByteArray* data) override;

  virtual int getEnergy() const { return energy; }
  virtual void setEnergy(int _enery) { this->energy = _enery; }

 protected:
  int energy = 100;
};

#endif  // BASEBASIS_H
