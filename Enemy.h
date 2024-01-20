//
// Created by barto on 17.01.2024.
//
#pragma once
#ifndef PROJEKT_ENEMY_H
#define PROJEKT_ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(sf::Vector2f &position, sf::Texture &texture,  int enemyType);
    void update(sf::RenderWindow &window, float &dt);
    void draw (sf::RenderWindow &window);
    void move(sf::Vector2f &offset);
    bool movingRight;
    bool movingLeft;
    bool movingDown;
    bool movingUp;
    sf::Sprite& getEnemy();
    static std::vector<Enemy*> &getEnemiesVector();
private:
    sf::Sprite enemy;
    sf::Vector2f startingPosition;
    int enemyType;
    static std::vector<Enemy*> enemies;
public:
    int getEnemyType() const;
};


#endif //PROJEKT_ENEMY_H