#ifndef GAMEELEMENTFACTORY_H
#define GAMEELEMENTFACTORY_H

#include "ibasegameelement.h"
#include "GameElements/basetank.h"
#include "GameElements/basebulet.h"
#include "GameElements/basebasis.h"

inline IBaseGameElement* getElement(GameElementData& data) {
  switch (((eBaseGameElementType)data.type)) {
    case eGrass:
      return new IBaseGameElement(data);
    case eSimpleTank:
      return new BaseTank(data);
    case eBasis:
      return new BaseBasis(data);
    case eBullet:
      return new BaseBulet(data);
    default:
      return new IBaseGameElement(data);
  }
}

#endif  // GAMEELEMENTFACTORY_H
