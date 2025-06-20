#include "ctower.h"

ctower::ctower() { 
    _location = cpoint(0, 0, 0); 
}

cpoint ctower::getLocation() const { 
    return _location; 
}

void ctower::setLocation(const cpoint& tl) { 
    _location = tl; 
}
void ctower::setMapForBullet(cpoint map[][cpoint::MAP_COL]) {
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _cb.updateMap(i, j, map[i][j]);
}
void ctower::calcPathBullet() { 
    _cb.calcPathBullet(_location); 
}

cbullet& ctower::getBullet() { 
    return _cb; 
}
