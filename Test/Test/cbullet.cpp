#include "cbullet.h"
#include <vector>
#include <cmath>      
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "cenemy.h"

using namespace std;

cbullet::cbullet() {
    _n = 0;
    _speed = 4;
    _curr = cpoint(0, 0, 0);
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint(0, 0, 0);
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = cpoint(0, 0, 0);
}
void cbullet::updateMap(int i, int j, cpoint v) {
    if (i >= 0 && i < cpoint::MAP_ROW && j >= 0 && j < cpoint::MAP_COL)
        _m[i][j] = v;
}
cpoint cbullet::getCurr() const { return _curr; }
void cbullet::setCurr(const cpoint& tcurr) { _curr = tcurr; }
cpoint* cbullet::getP() { return _p; }
int cbullet::getSpeed() const { return _speed; }
int cbullet::getN() const { return _n; }
void cbullet::setN(int tn) { if (tn >= 0 && tn <= cpoint::MAP_ROW * cpoint::MAP_COL) _n = tn; }
void cbullet::setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 20) _speed = tspeed; }

int cbullet::queryCFromRowCol(int row, int col) const {
    if (row < 0 || row >= cpoint::MAP_ROW || col < 0 || col >= cpoint::MAP_COL)
        return -2;
    return _m[row][col].getC();
}

int cbullet::calcPathBullet(const cpoint& tower) {
    int row = tower.getRow(), col = tower.getCol(), i = 0;
    do {
        col++; row--;
        if (queryCFromRowCol(row, col) == 0) {
            _p[i] = cpoint(row, col, 0);
            i += 2;
        }
        else break;
    } while (i < cpoint::MAP_ROW * cpoint::MAP_COL);
    _n = i;
    for (i = 1; i < _n; i += 2) {
        _p[i] = cpoint(_p[i - 1].getRow(), _p[i - 1].getCol(), 0); // center cell, hoặc tùy path bạn muốn
    }
    if (_n > 0)
        _curr = _p[0];
    return _n;
}

bool cbullet::checkCollision(const cenemy& enemy) const {
    // Compare bullet's current grid position with enemy's grid position
    cpoint enemyPos = enemy.getCurr();
    return _curr.getRow() == enemyPos.getRow() && _curr.getCol() == enemyPos.getCol();
}

void cbullet::trackEnemy(const cenemy& enemy) {
    cpoint enemyPos = enemy.getCurr();
    int bulletRow = _curr.getRow();
    int bulletCol = _curr.getCol();
    int enemyRow = enemyPos.getRow();
    int enemyCol = enemyPos.getCol();

    // Move bullet one step closer to the enemy in row and/or col
    if (bulletRow < enemyRow) bulletRow++;
    else if (bulletRow > enemyRow) bulletRow--;

    if (bulletCol < enemyCol) bulletCol++;
    else if (bulletCol > enemyCol) bulletCol--;

    _curr = cpoint(bulletRow, bulletCol, 0);
}


