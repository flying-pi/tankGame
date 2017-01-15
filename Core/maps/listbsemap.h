#ifndef LISTBSEMAP_H
#define LISTBSEMAP_H

#include <QList>
#include "imap.h"

class ListBseMap : public IMap {
 public:
  ListBseMap(double width, double heigth);
  ListBseMap();
  ~ListBseMap();
  // IMap interface
 public:
  virtual QSizeF* getSize();
  virtual void insertElement(IBaseGameElement* element, QVector3D* point);
  virtual void proccessAllInR(IBaseGameElement* element,
                              double r,
                              mapOperator op);
  virtual int getCount();
  virtual void updateFromDiff(DiffCard* diff);
  IBaseGameElement* getElementAtPosition(int pos);

 protected:
  QList<IBaseGameElement*>* items;
  QSizeF* size;
  /**
   * @brief updateItem update items in map
   * @param gameEleement element with information for update
   * @param isReplace if true than replace old item with @gameEleement. Otherway
   * delete from map list
   */
  void updateItem(IBaseGameElement* gameEleement, bool isReplace = true);
};

#endif  // LISTBSEMAP_H
