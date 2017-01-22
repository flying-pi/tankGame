#include "mapiniter.h"
#include "coreutil.h"

MapIniter::MapIniter() {}

IMap* MapIniter::initSimapleMap() {
  const int mapW = 1000;
  const int mapH = 1000;

  IMap* result = new ListBseMap(mapW, mapH);
  for (int i = 0; i < 400; i++) {
    IBaseGameElement* item = getRandomGrass(mapW, mapH);
    item->setName(codingNum(result->getCount()));
    result->insertElement(item);
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
