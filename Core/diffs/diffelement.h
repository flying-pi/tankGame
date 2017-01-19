#ifndef DIFFELEMENT_H
#define DIFFELEMENT_H

#include "../ibasegameelement.h"
#include "gameelementfactory.h"
#include <Qt>

enum eDiffType { eNew, eChange, eDeleted, eEmpty };

class DiffElement {
 public:
  ~DiffElement();
  DiffElement();
  DiffElement(eDiffType type, IBaseGameElement* data);
  friend QDataStream& operator<<(QDataStream& stream,
                                 const DiffElement& myclass) {
    stream << ((int)myclass.type);
    IBaseGameElement& gameElement = (*myclass.data);
    return stream << gameElement;
  }
  friend QDataStream& operator>>(QDataStream& stream, DiffElement& myclass) {
    int type;
    GameElementData item;
    stream >> type >> item;
    myclass.data = getElement(item);
    myclass.type = (eDiffType)type;
    return stream;
  }
  eDiffType type;
  IBaseGameElement* data;
  uint64_t time;
};

#endif  // DIFFELEMENT_H
