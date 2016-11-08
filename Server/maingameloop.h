#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include "imap.h"

class MainGameLoop
{
public:
    ~MainGameLoop();
    static inline MainGameLoop * getInstance(){
        if(instance == nullptr){
            instance = new MainGameLoop();
        }
        return instance;
    }

    void start();

private:
    static MainGameLoop *instance ;
    IMap *map;
    MainGameLoop();
};

MainGameLoop *MainGameLoop::instance = nullptr;


#endif // MAINGAMELOOP_H
