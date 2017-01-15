#ifndef DIFFELEMENT_H
#define DIFFELEMENT_H

#include "../ibasegameelement.h"
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
    QDataStream& result = stream >> type >> (*myclass.data);
    myclass.type = (eDiffType)type;
    return result;
  }
  eDiffType type;
  IBaseGameElement* data;
  uint64_t time;
};

#endif  // DIFFELEMENT_H
