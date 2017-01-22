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
  DiffElement(DiffElement& element);
  DiffElement(eDiffType type, IBaseGameElement* data);
  friend QDataStream& operator<<(QDataStream& stream,
                                 const DiffElement& myclass) {
    stream << ((int)myclass.type);
    return stream << (*myclass.data);
  }
  friend QDataStream& operator>>(QDataStream& stream, DiffElement& myclass) {
    int type;
    myclass.data->defaultInit();
    stream >> type >> (*myclass.data);
    myclass.type = (eDiffType)type;
    return stream;
  }
  eDiffType type;
  uint64_t time;

  inline GameElementData* getData() { return data; }
  IBaseGameElement* generateGameElementInstance();

  void update(DiffElement* element);

 protected:
  GameElementData* data;
};

#endif  // DIFFELEMENT_H
