#ifndef BASETANK_H
#define BASETANK_H
#include "../ibasegameelement.h"
#include "basebulet.h"

class BaseTank : public IBaseGameElement {
 public:
  BaseTank();

 public:
  virtual void setType(int value) override;
  virtual BaseBulet generateBullet();
  virtual void setAdditionakData(QByteArray* data);
  virtual QByteArray* getAdditionalData();

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
