#include <QPoint>
#include <QPointF>
#include "../ibasegameelement.h"
#include "math.h"

double distanceBetweenElement(IBaseGameElement* el1, IBaseGameElement* el2) {
  if (el1 == NULL || el2 == NULL)
    return 0;
  if (el1 == el2)
    return 0;
  const QVector3D* p1 = el1->getPosition();
  const QVector3D* p2 = el2->getPosition();
  double dx = p1->x() - p2->x();
  double dy = p1->y() - p2->x();
  double dz = p1->z() - p2->z();
  return sqrt(dx * dx + dy * dy + dz * dz);
}
