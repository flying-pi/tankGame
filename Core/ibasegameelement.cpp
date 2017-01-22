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

QDataStream& operator<<(QDataStream& stream, GameElementData& myclass) {
  stream << (*myclass.position);
  stream << (*myclass.helth);
  stream << (*myclass.weight);
  stream << (*myclass.transitWeight);
  stream << (*myclass.additionalData);
  stream << myclass.type;
  stream << myclass.name;
  stream << myclass.rVision;
  return stream;
}

void IBaseGameElement::copyData(GameElementData& out) {
  out.position = new QVector3D(*position);
  out.helth = new InfinityDouble(*helth);
  out.weight = new InfinityDouble(*weight);
  out.transitWeight = new InfinityDouble(*transitWeight);
  out.additionalData = new QByteArray(*additionalData);
  out.type = type;
  out.name = name;
  out.rVision = rVision;
}

void IBaseGameElement::init(GameElementData& data) {
  setHelth(data.helth);
  setWeight(data.weight);
  setTransitWeight(data.transitWeight);
  setPosition(data.position);
  setName(data.name);
  setAdditionakData(data.additionalData);
  setRVision(data.rVision);
  setType(data.type);
}
