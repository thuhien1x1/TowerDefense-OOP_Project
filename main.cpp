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

vector<Vector2f> convertPath(cpoint* path, int maxStep) {
    vector<Vector2f> result;
    for (int i = 0; i < maxStep; i++)
        result.push_back(Vector2f(path[i].getPixelX(), path[i].getPixelY()));
    return result;
}

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

    vector<pair<CircleShape, int>> bullets;
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
        if (!towers.empty() && shootTimer > 1.f) {
            shootTimer = 0.f;
            cpoint towerPoint = cpoint::fromXYToRowCol(towers[0].getPosition().x, towers[0].getPosition().y);
            int nPath = bulletLogic.calcPathBullet(towerPoint);
            if (nPath > 0) {
                CircleShape bulletShape(5.f);
                bulletShape.setFillColor(Color::Red);
                bulletShape.setOrigin(5.f, 5.f);
                bulletShape.setPosition(bulletLogic.getP()[0].getPixelX(), bulletLogic.getP()[0].getPixelY());
                bullets.push_back(std::make_pair(bulletShape, 0));
            }
        }

        for (auto& bullet : bullets) {
            CircleShape& shape = bullet.first;
            int& pathIndex = bullet.second;
            if (pathIndex + 1 < bulletLogic.getN()) {
                Vector2f from = shape.getPosition();
                Vector2f to(
                    bulletLogic.getP()[pathIndex + 1].getPixelX(),
                    bulletLogic.getP()[pathIndex + 1].getPixelY()
                );
                Vector2f dir = to - from;
                float len = sqrt(dir.x * dir.x + dir.y * dir.y);
                if (len > 1.f) {
                    Vector2f normalizedDir = Vector2f(dir.x / len, dir.y / len);
                    float scalar = bulletLogic.getSpeed() * deltaTime * 60.f;
                    Vector2f moveVec(normalizedDir.x * scalar, normalizedDir.y * scalar);
                    shape.move(moveVec);
                }
                else
                    pathIndex++;
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        for (const auto& tower : towers)
            window.draw(tower);

        for (const auto& e : enemies)
            window.draw(e.sprite);

        for (const auto& bullet : bullets)
            window.draw(bullet.first);

        window.display();
    }
}