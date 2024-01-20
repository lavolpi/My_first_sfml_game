//
// Created by barto on 17.01.2024.
//

#include "Enemy.h"
std::vector<Enemy*> Enemy::enemies;
Enemy::Enemy(sf::Vector2f &position, sf::Texture &texture, int enemyType) {
    enemy.setPosition(position);
    enemy.setTexture(texture);
    enemies.push_back(this);
    this->enemyType = enemyType;
    this->startingPosition = position;
}

void Enemy::update(sf::RenderWindow &window, float &dt) {
    sf::Vector2f movement;
    if(this->enemyType == 1)
    {
        if (movingRight)
        {
            movement = sf::Vector2f(150.f * dt, 0.f);
            if (enemy.getPosition().x > this->startingPosition.x + 100)
            {
                movingRight = false;
            }
        }
        else
        {
            movement = sf::Vector2f(-150.f * dt, 0.f);
            if (enemy.getPosition().x < this->startingPosition.x - 100)
            {
                movingRight = true;
            }
        }
    }
    else if (this->enemyType == 2)
    {
        if (movingUp)
        {
            movement = sf::Vector2f(0.f, -150.f * dt);
            if (enemy.getPosition().y <= this->startingPosition.y - 150)
            {
                movingUp = false;
            }
        }
        else
        {
            movement = sf::Vector2f(0.f, 150.f * dt);
            if (enemy.getPosition().y >= this->startingPosition.y)
            {
                movingUp = true;
            }
        }
    }
    else if (this->enemyType == 3)
    {
        movement = sf::Vector2f(0.f, 0.f);
    }

    this->move(movement);
    this->draw(window);
}

void Enemy::move(sf::Vector2f &offset) {
    enemy.move(offset);
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(enemy);
}

std::vector<Enemy*>& Enemy::getEnemiesVector() {
    return enemies;
}

sf::Sprite& Enemy::getEnemy() {
    return enemy;
}

int Enemy::getEnemyType() const {
    return enemyType;
}


