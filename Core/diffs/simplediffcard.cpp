#include "simplediffcard.h"

SimpleDiffCard::SimpleDiffCard() {}

int SimpleDiffCard::getCountOfDiff() {
  return items.size();
}

DiffCard* SimpleDiffCard::subdiffForElements(QList<IBaseGameElement*> items) {}

void SimpleDiffCard::updateFromOtherCard(DiffCard* card) {}
