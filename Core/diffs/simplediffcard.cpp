#include "simplediffcard.h"

SimpleDiffCard::SimpleDiffCard() {}

int SimpleDiffCard::getCountOfDiff() {
  return items.size();
}

DiffCard* SimpleDiffCard::subdiffForElements(QList<IBaseGameElement*> items) {return nullptr;}

// enum eDiffType { eNew, eChange, eDeleted, eEmpty };

void SimpleDiffCard::updateFromOtherCard(DiffCard* card) {
  if (items.size() == 0) {
    for (int i = 0; i < card->getCountOfDiff(); i++) {
      items.append(new DiffElement(*card->at(i)));
    }
    return;
  }
  for (int i = 0; i < card->getCountOfDiff(); i++) {
    for (int j = 0; j < items.size(); j++) {
      if (card->at(i)->getData()->name == items.at(j)->getData()->name) {
        switch (card->at(i)->type) {
          case eNew:
          case eChange:
            items.at(j)->update(card->at(i));
            break;
          case eDeleted:
            delete items.at(j);
            items.removeAt(j);
            break;
          case eEmpty:
            break;
        }
        break;
      }
      if (j == items.size() - 1) {
        items.append(new DiffElement(*card->at(i)));
      }
    }
  }
}
