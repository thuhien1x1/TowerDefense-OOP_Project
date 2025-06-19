#pragma once
#include "cmap.h"

class cgame
{
    cmap _map;
public:
    cgame();
    void startGame();
    cmap& getMap() { return _map; }
};
