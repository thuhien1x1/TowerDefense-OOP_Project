#include "ctower.h"

<<<<<<< HEAD
ctower::ctower()
{ 
    _location = cpoint(0, 0, 0); 
}

// getters setters
cbullet& ctower::getBullet()
{
    return _cb;
}
cpoint ctower::getLocation() const
{ 
    return _location; 
}
void ctower::setLocation(const cpoint& tl)
{
    _location = tl;
}

// just call once after level loads
void ctower::setMapForBullet(cpoint map[][cpoint::MAP_COL])
{
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _cb.updateMap(i, j, map[i][j]);
}

void ctower::calcPathBullet()
{ 
    _cb.setTargetIdx(1);
    _cb.activate();
    _cb.calcPathBullet(_location); 
}
=======
ctower::ctower() : _shootTimer(0.f), _targetEnemyIdx(-1) {}

int ctower::calcPathBullet() {
    return _cb.calcPathBullet(_location);
}

void ctower::init(const sf::Texture& tex, float x, float y) {
    _sprite.setTexture(tex);
    _sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    _sprite.setPosition(x, y);
    _location = cpoint::fromXYToRowCol(x, y);
}

const sf::Sprite& ctower::getSprite() const { return _sprite; }

void ctower::setLocation(const cpoint& loc) { _location = loc; }
cpoint ctower::getLocation() const { return _location; }

void ctower::resetShootTimer() { _shootTimer = 0.f; }
void ctower::addShootTimer(float dt) { _shootTimer += dt; }
float ctower::getShootTimer() const { return _shootTimer; }

int ctower::getTargetEnemyIdx() const { return _targetEnemyIdx; }
void ctower::setTargetEnemyIdx(int idx) { _targetEnemyIdx = idx; }

void ctower::setMapForBullet(cpoint map[][cpoint::MAP_COL]) {
    _cb.updateMap(map);
}

cbullet& ctower::getBullet() { return _cb; }

>>>>>>> github-desktop-chinnnn3107/Update3
