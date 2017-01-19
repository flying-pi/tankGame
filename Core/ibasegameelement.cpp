#include "ibasegameelement.h"

QDataStream& operator>>(QDataStream& stream, GameElementData& myclass) {
  stream >> (*myclass.position);
  stream >> (*myclass.helth);
  stream >> (*myclass.weight);
  stream >> (*myclass.transitWeight);
  stream >> (*myclass.additionalData);
  stream >> myclass.type;
  stream >> myclass.name;
  stream >> myclass.rVision;
  return stream;
}
