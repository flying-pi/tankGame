#include "diffelement.h"

DiffElement::DiffElement() {
  data = new IBaseGameElement();
  type = eEmpty;
  time = 0;
}

DiffElement::DiffElement(eDiffType type, IBaseGameElement* data) {
  this->type = type;
  this->data = data;
  time = 0;
}
