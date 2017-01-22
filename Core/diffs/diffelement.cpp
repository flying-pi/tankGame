#include "diffelement.h"

DiffElement::~DiffElement() {
  delete data;
}

DiffElement::DiffElement() {
  data = new GameElementData();
  type = eEmpty;
  time = 0;
}

DiffElement::DiffElement(DiffElement& element) {
  data = new GameElementData();
  type = eEmpty;
  time = 0;
  this->update(&element);
}

DiffElement::DiffElement(eDiffType type, IBaseGameElement* data) {
  this->type = type;
  this->data = new GameElementData();
  data->copyData(*this->data);
  time = 0;
}

IBaseGameElement* DiffElement::generateGameElementInstance() {
  return getElement(*data);
}

void DiffElement::update(DiffElement* element) {
  this->type = element->type;
  this->time = element->time;
  this->data->position = new QVector3D(*element->getData()->position);
  this->data->helth = new InfinityDouble(*element->getData()->helth);
  this->data->weight = new InfinityDouble(*element->getData()->weight);
  this->data->transitWeight =
      new InfinityDouble(*element->getData()->transitWeight);
  this->data->additionalData =
      new QByteArray(*element->getData()->additionalData);
  this->data->type = element->getData()->type;
  this->data->name = element->getData()->name;
  this->data->rVision = element->getData()->rVision;
}
