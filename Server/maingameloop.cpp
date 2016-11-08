#include "maingameloop.h"
#include "mapiniter.h"

MainGameLoop::MainGameLoop()
{
    map = MapIniter().initSimapleMap();
}

MainGameLoop::~MainGameLoop()
{
    delete map;
}

void MainGameLoop::start()
{

}

