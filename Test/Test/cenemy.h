#pragma once
#include "cpoint.h"

class cenemy
{
private:
    int _speed;
    cpoint _start, _end, _curr;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    int _pathLength;
    int dd[4], dc[4];

public:
    cenemy();
    cenemy(cpoint tstart, cpoint tend, cpoint tcurr);

    cpoint* getP() { return _p; }
    int getPathLength() const { return _pathLength; }
    cpoint getStart() const { return _start; }
    cpoint getEnd() const { return _end; }
    int getSpeed() const { return _speed; }
    cpoint getCurr() const { return _curr; }

    void setSpeed(int tspeed);
    void setStart(const cpoint& tstart);
    void setEnd(const cpoint& tend);
    void setCurr(const cpoint& tcurr);

    void findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e);

private:
    void calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e);
};
