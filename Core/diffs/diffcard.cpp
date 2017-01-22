#include "diffcard.h"

DiffCard::DiffCard(QObject* parent) : QObject(parent) {}

void DiffCard::loadFromList(QList<DiffElement*>& newItems) {
  foreach (auto i, newItems) { append(i); }
}

void DiffCard::loadFromList(QList<DiffElement*>* newItems) {
  for (int i = 0; i < newItems->size(); i++)
    append(newItems->at(i));
}

void DiffCard::freeItems() {
  for (int i = 0; i < getCountOfDiff(); i++) {
    delete at(i);
  }
  clear();
}
