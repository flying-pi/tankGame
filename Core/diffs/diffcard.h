#ifndef DIFFCARD_H
#define DIFFCARD_H

#include <QObject>
#include <QList>
#include "diffelement.h"
#include "../ibasegameelement.h"

class DiffCard : public QObject {
  Q_OBJECT
 public:
  explicit DiffCard(QObject* parent = 0);

  virtual void loadFromList(QList<DiffElement*>& newItems);
  virtual void loadFromList(QList<DiffElement*>* newItems);
  virtual int getCountOfDiff() = 0;
  virtual DiffElement* at(int i) = 0;
  virtual DiffCard* subdiffForElements(QList<IBaseGameElement*> items) = 0;
  virtual void append(DiffElement* diff) = 0;
  virtual void clear() = 0;
  virtual void updateFromOtherCard(DiffCard* card) = 0;

  /**
   * @brief freeItems simular to claer but also call destructor for diff
   * elemenst
   */
  virtual void freeItems();

 signals:

 public slots:
};

#endif  // DIFFCARD_H
