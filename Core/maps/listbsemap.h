#ifndef LISTBSEMAP_H
#define LISTBSEMAP_H

#include <QList>
#include "imap.h"

class ListBseMap : public IMap {
 public:
  ListBseMap(double width, double heigth);
  ~ListBseMap();
  // IMap interface
 public:
  QSizeF* getSize();
  void insertElement(IBaseGameElement* element, QVector3D* point);
  void proccessAllInR(IBaseGameElement* element, double r, mapOperator op);
  int getCount();
  IBaseGameElement* getElementAtPosition(int pos);

 protected:
  QList<IBaseGameElement*>* items;
  QSizeF* size;
};

#endif  // LISTBSEMAP_H
