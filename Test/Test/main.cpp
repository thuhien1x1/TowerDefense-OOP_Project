#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility> 
#include "cpoint.h"
#include "cmap.h"
#include "cenemy.h"
#include "ctower.h"
#include "cbullet.h"

using namespace std;
using namespace sf;

// Test
vector<Vector2f> convertPath(cpoint* path, int maxStep) {
    vector<Vector2f> result;
    for (int i = 0; i < maxStep; i++)
        result.push_back(Vector2f(path[i].getPixelX(), path[i].getPixelY()));
    return result;
}

struct Bullet {
    CircleShape shape;
    int targetEnemyIdx; // Index of the enemy this bullet is tracking
    bool active = true;
};

std::vector<Bullet> bullets;

int main() {
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        cerr << "Failed to load background!" << endl;
        return -1;
    }

    Texture towerTexture;
    if (!towerTexture.loadFromFile("tower.png")) {
        cerr << "Failed to load tower image!" << endl;
        return -1;
    }

    Texture enemyTexture;
    if (!enemyTexture.loadFromFile("blockbott4.png")) {
        cerr << "Failed to load enemy image!" << endl;
        return -1;
    }

    Vector2u textureSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode(textureSize.x, textureSize.y), "Tower Defense SFML");
    Sprite backgroundSprite(backgroundTexture);

    cmap map;
    cenemy& ce = map.getEnemy();
    cpoint* pathData = ce.getP();
    int pathLen = ce.getPathLength();
    auto path = convertPath(pathData, pathLen);

    struct Enemy {
        Sprite sprite;
        int currentTarget = 1;
        bool reachedEnd = false;
        int hitCount = 0;
    };
    vector<Enemy> enemies;

    for (int i = 0; i < 10; i++) {
        Sprite sprite;
        sprite.setTexture(enemyTexture);
        sprite.setOrigin(enemyTexture.getSize().x / 2.f, enemyTexture.getSize().y / 2.f);
        sprite.setScale(0.5f, 0.5f);
        sprite.setPosition(path[0].x - i * 80.f, path[0].y);
        enemies.push_back({ sprite, 1, false, 0 });
    }

    float speed = 120.f;
    vector<Sprite> towers;

    cbullet bulletLogic;

    Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                cpoint clicked = cpoint::fromXYToRowCol(mouseX, mouseY);
                int r = clicked.getRow(), c = clicked.getCol();

                if (r >= 0 && r < cpoint::MAP_ROW && c >= 0 && c < cpoint::MAP_COL) {
                    if (map.getMap()[r][c].getC() == -1) {
                        Sprite towerSprite;
                        towerSprite.setTexture(towerTexture);
                        towerSprite.setOrigin(towerTexture.getSize().x / 2.f, towerTexture.getSize().y / 2.f);
                        towerSprite.setPosition(map.getMap()[r][c].getPixelX(), map.getMap()[r][c].getPixelY());
                        towers.push_back(towerSprite);
                    }
                }
            }
        }

        for (auto& e : enemies) {
            if (!e.reachedEnd && e.currentTarget < static_cast<int>(path.size())) {
                Vector2f pos = e.sprite.getPosition();
                Vector2f target = path[e.currentTarget];
                Vector2f dir = target - pos;
                float length = sqrt(dir.x * dir.x + dir.y * dir.y);
                if (length < 1.f) {
                    e.currentTarget++;
                    if (e.currentTarget >= static_cast<int>(path.size()))
                        e.reachedEnd = true;
                }
                else {
                    dir /= length;
                    e.sprite.move(dir * speed * deltaTime);
                }
            }
        }

        static float shootTimer = 0.f;
        shootTimer += deltaTime;
        if (!towers.empty() && shootTimer > 1.f && !enemies.empty()) {
            shootTimer = 0.f;
            cpoint towerPoint = cpoint::fromXYToRowCol(towers[0].getPosition().x, towers[0].getPosition().y);
            int nPath = bulletLogic.calcPathBullet(towerPoint);
            if (nPath > 0) {
                // Find the first active enemy as the target
                int targetIdx = -1;
                for (size_t i = 0; i < enemies.size(); ++i) {
                    if (!enemies[i].reachedEnd) {
                        targetIdx = static_cast<int>(i);
                        break;
                    }
                }
                if (targetIdx != -1) {
                    Bullet b;
                    b.shape = CircleShape(5.f);
                    b.shape.setFillColor(Color::Red);
                    b.shape.setOrigin(5.f, 5.f);
                    b.shape.setPosition(bulletLogic.getP()[0].getPixelX(), bulletLogic.getP()[0].getPixelY());
                    b.targetEnemyIdx = targetIdx;
                    b.active = true;
                    bullets.push_back(b);
                }
            }
        }

        for (auto& bullet : bullets) {
            if (!bullet.active) continue;
            if (bullet.targetEnemyIdx < 0 || bullet.targetEnemyIdx >= static_cast<int>(enemies.size())) {
                bullet.active = false;
                continue;
            }
            Enemy& target = enemies[bullet.targetEnemyIdx];
            if (target.reachedEnd) {
                bullet.active = false;
                continue;
            }
            Vector2f bulletPos = bullet.shape.getPosition();
            Vector2f enemyPos = target.sprite.getPosition();
            Vector2f dir = enemyPos - bulletPos;
            float len = sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len < 10.f) { // Collision threshold (adjust as needed)
                bullet.active = false;
                target.hitCount++;
                // Optionally, mark enemy as dead or remove it if hitCount exceeds threshold
                continue;
            }
            if (len > 0.1f) {
                dir /= len;
                float moveSpeed = bulletLogic.getSpeed() * deltaTime * 60.f;
                bullet.shape.move(dir * moveSpeed);
            }
        }

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.active; }),
            bullets.end()
        );

        window.clear();
        window.draw(backgroundSprite);

        for (const auto& tower : towers)
            window.draw(tower);

        for (const auto& e : enemies)
            window.draw(e.sprite);

        for (const auto& bullet : bullets)
            window.draw(bullet.shape);

        window.display();
    }
}