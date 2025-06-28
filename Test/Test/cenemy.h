#pragma once
#include "cpoint.h"
#include <SFML/Graphics.hpp>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class cenemy
{
private:
    int _speed;
    cpoint _start, _end, _curr;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    int _pathLength;
    int dd[4], dc[4];
    // Add
    int _health;
    float _posX, _posY; 
    sf::Sprite _sprite;
    bool _reachedEnd;
    int _currentTarget;

    // runtime properties
    int currentTarget = 1;
    bool reachEnd = false;
    int hitCount = 0;
public:
    cenemy();
    cenemy(cpoint tstart, cpoint tend, cpoint tcurr);

    // runtime process
    void findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e);
    void move(float dt);
    void onHit();
    bool isDead() const;
    bool isReachedEnd() const;

    void setCurr(const cpoint& tcurr);
    cpoint getCurr() const;

    // path access
    cpoint* getP();
    int getPathLength() const;
    int getCurrentTarget() const;
    void setCurrentTarget(int);
    
    // getters, setters
    cpoint getStart() const;
    cpoint getEnd() const;
    int getSpeed() const;
    void setStart(const cpoint& tstart);
    void setEnd(const cpoint& tend);
<<<<<<< HEAD
    void setSpeed(int tspeed);
=======
    void setCurr(const cpoint& tcurr);

    void reachEnd() { _reachedEnd = true; }
    bool hasReachedEnd() const { return _reachedEnd; }
    void findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e);

    // Health logic
    int getHealth() const { return _health; }
    void setHealth(int hp) { _health = hp; }
    bool isDead() const { return _health <= 0; }
    void takeDamage(int damage);

    // Position and movement
    void init(const sf::Texture& tex, float x, float y, int hp);
    void updateSprite();

    float getX() const { return _posX; }
    int getCurrentTarget() const { return _currentTarget; } // Control enemy movement along route, check when enemy reaches destination, update next point on route
    float getY() const { return _posY; }
    const sf::Sprite& getSprite() const { return _sprite; }

    void setPosition(float x, float y);
    void setCurrentTarget(int t) { _currentTarget = t; }
    void move(float dx, float dy);
    void incrementTarget() { _currentTarget++; }

>>>>>>> github-desktop-chinnnn3107/Update3
private:
    void calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e);
};