#ifndef BASETANK_H
#define BASETANK_H
#include "../ibasegameelement.h"
#include "basebulet.h"

class BaseTank : public IBaseGameElement {
 public:
  BaseTank();
  BaseTank(GameElementData& data);

 public:
  using IBaseGameElement::setType;
  virtual void setType(int value) override;

  using IBaseGameElement::setAdditionakData;
  virtual void setAdditionakData(QByteArray* data) override;
  virtual QByteArray* getAdditionalData() const;

  virtual void setDirection(double _direction);
  virtual double getDirection() const { return direction; }

  virtual void setSpeed(double _speed);
  virtual double getSpeed() const { return speed; }

 protected:
  double direction = 0;
  double speed = 0;
  /**
   * @brief fireType
   * 0  for non fire
   * -1 for single fire
   * if fireType > 0 then fire will be call evry fireType tik of game
   */
  int fireType = 0;
};

#endif  // BASETANK_H
