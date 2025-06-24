#pragma once
#include "cpoint.h"
#include "cenemy.h" // Make sure to include the enemy header

class cbullet
{
    int _n, _speed;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
    cpoint _curr;

public:
    cbullet();
    void updateMap(int i, int j, cpoint v);
    cpoint getCurr() const;
    void setCurr(const cpoint& tcurr);
    cpoint* getP();
    int getSpeed() const;
    int getN() const;
    void setN(int tn);
    void setSpeed(int tspeed);
    int queryCFromRowCol(int row, int col) const;
    int calcPathBullet(const cpoint& tower);

    // Bullet collision detection
    bool checkCollision(const cenemy& enemy) const;

    // Move bullet one step toward the enemy's current position
    void trackEnemy(const cenemy& enemy);
};
