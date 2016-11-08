#ifndef MAPINITER_H
#define MAPINITER_H

#include "imap.h"
#include "maps/listbsemap.h"
#include "ibasegameelement.h"

class MapIniter
{
public:
    MapIniter();
    IMap *initSimapleMap();

protected:
    IBaseGameElement *getRandomGrass(double maxWidth,double maxHeigth);

};

#endif // MAPINITER_H
