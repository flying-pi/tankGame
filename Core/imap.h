#ifndef IMAP_H
#define IMAP_H

#include <QSizeF>
#include <QPointF>
#include "ibasegameelement.h"

// typedef bool(mapOperator)(IBaseGameElement* element);

typedef std::function<bool(IBaseGameElement*)> mapOperator;

class IMap {
 public:
  IMap();
  virtual QSizeF* getSize() = 0;
  virtual void insertElement(IBaseGameElement* element, QVector3D* point) = 0;
  virtual void proccessAllInR(IBaseGameElement* element,
                              double r,
                              mapOperator) = 0;
  virtual int getCount() = 0;
  virtual IBaseGameElement* getElementAtPosition(int pos) = 0;
};

#endif  // IMAP_H
