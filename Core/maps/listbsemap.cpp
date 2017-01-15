#include "listbsemap.h"
#include "../util/baseutil.h"

ListBseMap::ListBseMap(double width, double heigth) {
  size = new QSizeF(width, heigth);
  items = new QList<IBaseGameElement*>();
}

ListBseMap::ListBseMap() {
  items = new QList<IBaseGameElement*>();
}

ListBseMap::~ListBseMap() {
  delete items;
  delete size;
}

QSizeF* ListBseMap::getSize() {
  delete size;
}

void ListBseMap::insertElement(IBaseGameElement* element, QVector3D* point) {
  items->append(element);
}

void ListBseMap::proccessAllInR(IBaseGameElement* element,
                                double r,
                                mapOperator op) {
  for (int i = 0; i < items->size(); i++) {
    IBaseGameElement* el = items->at(i);
    if (element != el && distanceBetweenElement(el, element))
      op(el);
  }
}

int ListBseMap::getCount() {
  return items->size();
}

void ListBseMap::updateFromDiff(DiffCard* diff) {
  for (int i = 0; i < diff->getCountOfDiff(); i++) {
    switch (diff->at(i)->type) {
      case eNew:
        items->append(diff->at(i)->data);
        break;
      case eChange:
        updateItem(diff->at(i)->data);
        break;
      case eDeleted:
        updateItem(diff->at(i)->data, false);
        break;
      case eEmpty:
        break;
    };
  }
}

IBaseGameElement* ListBseMap::getElementAtPosition(int pos) {
  return items->at(pos);
}

void ListBseMap::updateItem(IBaseGameElement* gameEleement, bool isReplace) {
  for (int i = 0; i < items->size(); i++) {
    if ((*items->at(i)->getName()) == (*gameEleement->getName())) {
      delete items->at(i);
      items->removeAt(i);
      if (isReplace)
        items->append(gameEleement);
      else
        delete gameEleement;
    }
  }
}
