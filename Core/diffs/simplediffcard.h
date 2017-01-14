#ifndef SIMPLEDIFFCARD_H
#define SIMPLEDIFFCARD_H

#include "diffcard.h"
#include <QList>
#include "../ibasegameelement.h"

class SimpleDiffCard : public DiffCard {
 public:
  SimpleDiffCard();

 public:
  virtual int getCountOfDiff();
  virtual DiffCard* subdiffForElements(QList<IBaseGameElement*> items);
  virtual void updateFromOtherCard(DiffCard* card);
  virtual void clear() { items.clear(); }
  virtual DiffElement* at(int i) { return items.at(i); }
  virtual void append(DiffElement* diff) { items.append(diff); }

 protected:
  QList<DiffElement*> items;
};

#endif  // SIMPLEDIFFCARD_H
