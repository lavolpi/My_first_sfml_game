//
// Created by barto on 29.12.2023.
//

#include "Tile.h"

Tile::Tile(sf::Vector2f &position, sf::Texture &texture) : isCollidable(false), isDeadly(false){
    tile.setTexture(texture);
    this->tile.setPosition(position);
}
void Tile::draw(sf::RenderWindow &window)
{
    window.draw(this->tile);
}

sf::Sprite& Tile::getTile(){
    return this->tile;
}

bool Tile::getIsCollidable() const{
    return isCollidable;
}

void Tile::setIsCollidable(bool isCollidable){
    Tile::isCollidable = isCollidable;
}

void Tile::setIsDeadly(bool isDeadly){
    Tile::isDeadly = isDeadly;
}

bool Tile::isDeadly1() const{
    return isDeadly;
}
