//
// Created by barto on 29.12.2023.
//
#pragma once
#ifndef PROJEKT_PLAYER_H
#define PROJEKT_PLAYER_H
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Enemy.h"

class Player {
public:
    Player(sf::Vector2f &position, sf::Texture &texture);
    void draw(sf::RenderWindow &window);
    void move(sf::Vector2f &offset);
    void update(sf::RenderWindow &window, const float &dt);
    void collision(const std::vector<Tile> &tiles,std::vector<Enemy*> &enemies, sf::RenderWindow &window);
    void moveLeft(const float &dt);
    void moveRight(const float &dt);
    void jump();
    sf::Sprite getPlayer();
    int getJumpUpgrade() const;
    int getMoveSpeedUpgrade() const;
    int getImmortalUpgrade();
    bool isGameOver();
    bool isImmortal();
    void setImmortal(bool immortal);
private:
    sf::Sprite player;
    sf::Vector2f movement;
    float velocity;
    float jumpVelocity;
    float gravity;
    int jumpUpgrade;
    int moveSpeedUpgrade;
    int immortalUpgrade;
    bool canJump;
    bool isOnGround;
    bool collisionLeft;
    bool collisionRight;
    bool gameOver;
    bool immortal;
};


#endif //PROJEKT_PLAYER_H