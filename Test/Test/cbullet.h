#pragma once
#include "cpoint.h"
#include "cenemy.h" 
#include <SFML/Graphics.hpp>

class cbullet
{
private:
    int _n, _speed;
    cpoint _p[cpoint::MAP_ROW * cpoint::MAP_COL];
    cpoint _m[cpoint::MAP_ROW][cpoint::MAP_COL];
    cpoint _curr;
    // Add
    float _posX, _posY;
    bool _active;
    int _targetIdx;
    int _damage;
    sf::Sprite _sprite;

    bool active = false;
    int targetIndex = -1;
public:
    cbullet();
<<<<<<< HEAD

    // logic
    void updateMap(int i, int j, cpoint v);
=======
    void updateMap(cpoint map[][cpoint::MAP_COL]); // Update

    cpoint getCurr() const;
    cpoint* getP();
    int getSpeed() const;
    int getN() const;

    void setCurr(const cpoint& tcurr);
    void setN(int tn);
    void setSpeed(int tspeed);

>>>>>>> github-desktop-chinnnn3107/Update3
    int queryCFromRowCol(int row, int col) const;
    int calcPathBullet(const cpoint& tower);

    void trackEnemy(const cenemy& enemy); // Move bullet one step toward the enemy's current position
    bool checkCollision(const cenemy& enemy) const; // Bullet collision detection

<<<<<<< HEAD
    // getters
    cpoint getCurr() const;
    cpoint* getP();
    int getSpeed() const;
    int getN() const;
    int getTargetIndex() const;
    bool isActive() const;

    // setter
    void setCurr(const cpoint& tcurr);
    void setN(int tn);
    void setSpeed(int tspeed);
    void setTargetIdx(int idx);
    void activate();
    void deactivate();
=======
    // Move bullet one step toward the enemy's current position
    void trackEnemy(const cenemy& enemy, float deltaTime);

    // Position and movement
    void init(const sf::Texture& tex, float x, float y);
    void updateSprite();
    const sf::Sprite& getSprite() const { return _sprite; }
    
    float getX() const { return _posX; }
    float getY() const { return _posY; }

    void setPosition(float x, float y);
    void move(float dx, float dy);

    // Bullet logic
    int getTargetIdx() const { return _targetIdx; } // Returns the index of the current enemy target the bullet is tracking
    int getDamage() const { return _damage; } // Returns how much damage the bullet will deal on impact.

    void setTargetIdx(int idx) { _targetIdx = idx; } // Assign the index of the target enemy for the bullet to track.
    void setDamage(int dmg) { _damage = dmg; } // Define how much damage this bullet should inflict (useful for upgrade towers)

    bool isActive() const { return _active; } // Returns true if the bullet is still active (on screen, valid target), used to skip deactivated bullets.
    void deactivate() { _active = false; } // Marks the bullet as inactive after hitting an enemy or going off - screen, Prevents further updates or rendering.
>>>>>>> github-desktop-chinnnn3107/Update3
};
