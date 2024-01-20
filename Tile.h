//
// Created by barto on 29.12.2023.
//
#pragma once
#ifndef PROJEKT_TILE_H
#define PROJEKT_TILE_H
#include <SFML/Graphics.hpp>



class Tile{
public:
    Tile(sf::Vector2f &position, sf::Texture &texture);
    void draw(sf::RenderWindow &window);
    sf::Sprite &getTile();
    bool getIsCollidable() const;
    void setIsCollidable(bool isCollidable);

    bool isDeadly1() const;

    void setIsDeadly(bool isDeadly);

private:
sf::Sprite tile;
bool isCollidable;
bool isDeadly;
};


#endif //PROJEKT_TILE_H