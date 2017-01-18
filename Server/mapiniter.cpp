#include "mapiniter.h"

MapIniter::MapIniter() {}

IMap* MapIniter::initSimapleMap() {
  const int mapW = 100;
  const int mapH = 100;

  IMap* result = new ListBseMap(mapW, mapH);
  for (int i = 0; i < 400; i++) {
    IBaseGameElement* item = getRandomGrass(mapW, mapH);
    result->insertElement(item, item->getPosition());
  }
  return result;
}

IBaseGameElement* MapIniter::getRandomGrass(double maxWidth, double maxHeigth) {
  IBaseGameElement* result = new IBaseGameElement();
  result->setPosition(new QVector3D(
      (double)rand() / (double)RAND_MAX * maxWidth - maxWidth / 2,
      (double)rand() / (double)RAND_MAX * maxHeigth - maxHeigth / 2, 0));
  result->setHelth(InfinityDouble::InfinityValue());
  result->setTransitWeight(InfinityDouble::FromValue(0));
  result->setType(eBaseGameElementType::eGrass);
  return result;
}
