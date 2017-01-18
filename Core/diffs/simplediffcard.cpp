#include "simplediffcard.h"

SimpleDiffCard::SimpleDiffCard() {}

int SimpleDiffCard::getCountOfDiff() {
  return items.size();
}

DiffCard* SimpleDiffCard::subdiffForElements(QList<IBaseGameElement*> items) {}

// enum eDiffType { eNew, eChange, eDeleted, eEmpty };

void SimpleDiffCard::updateFromOtherCard(DiffCard* card) {
  //  for (int i = 0; i < card->getCountOfDiff(); i++) {
  //    for (int j = 0; j < items.size(); j++) {
  //      if (card->at(i)->data->getName() == items.at(j)->data->getName()) {
  //        switch (card->at(i)->type) {
  //          case eNew:
  //            break;
  //          case eChange:
  //            break;
  //          case eDeleted:
  //            break;
  //          case eEmpty:
  //            break;
  //        }
  //        break;
  //      }
  //    }
  //  }
}
