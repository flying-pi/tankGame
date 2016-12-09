#include "mapiniter.h"

MapIniter::MapIniter() {}

IMap* MapIniter::initSimapleMap() {
  const int mapW = 1000;
  const int mapH = 1000;

  IMap* result = new ListBseMap(mapW, mapH);
  for (int i = 0; i < 1000; i++) {
    IBaseGameElement* item = getRandomGrass(mapW, mapH);
    result->insertElement(item, *item->getPosition());
  }
  return result;
}

IBaseGameElement* MapIniter::getRandomGrass(double maxWidth, double maxHeigth) {
  IBaseGameElement* result = new IBaseGameElement();
  result->setPosition(
      new QPointF((double)rand() / (double)RAND_MAX * maxWidth,
                  (double)rand() / (double)RAND_MAX * maxHeigth));
  result->setHelth(InfinityDouble::InfinityValue());
  result->setTransitWeight(InfinityDouble::FromValue(0));
  return result;
}