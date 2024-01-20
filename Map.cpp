//
// Created by barto on 06.01.2024.
//

#include "Map.h"
Map::Map() = default;

void Map::initiateMap(sf::Texture &background, sf::Texture &grass, sf::Texture &shroom, sf::Texture &groundEnemy, sf::Texture &bat, sf::Texture &coin) {
int tileSize = 64;

for(int i = 0; i < tileMap.size(); i++)
    for (int j = 0; j<tileMap[i].size(); j++)
    {
        sf::Vector2f pos = sf::Vector2f(j * tileSize, i * tileSize);
     switch(tileMap[i][j])
     {
         case 0:
         {
             Tile tile (pos, background);
             tile.getTile().setScale(64.0f / 24.0f, 64.0f / 24.0f);
             this->colliisonMap.push_back(tile);
             break;
         }
         case 1:
         {
             Tile tile (pos, grass);
             tile.setIsCollidable(true);
             tile.getTile().setScale(64.0f / 18.0f, 64.0f / 18.0f);
             this->colliisonMap.push_back(tile);
             break;
         }
         case 2:
         {
             Tile tile (pos, shroom);
             tile.setIsDeadly(true);
             tile.getTile().setScale(64.0f / 18.0f, 64.0f / 18.0f);
             this->colliisonMap.push_back(tile);
             break;
         }
     }
    }

for(int i = 0; i < enemyMap.size(); i++)
    for(int j = 0; j<enemyMap[i].size(); j++)
    {
        sf::Vector2f pos = sf::Vector2f (j * tileSize, i * tileSize);
        switch(enemyMap[i][j])
        {
            case 1:
            {
                Enemy* enemy = new Enemy(pos, groundEnemy, 1);
                enemy->getEnemy().setScale(64.0f / 24.0f, 64.0f / 24.0f);
                this->enemiesMap.push_back(enemy);
                break;
            }
            case 2:
            {
                Enemy* enemy = new Enemy(pos, bat, 2);
                enemy->getEnemy().setScale(64.0f / 24.0f, 64.0f / 24.0f);
                this->enemiesMap.push_back(enemy);
                break;
            }
            case 3:
            {
                Enemy* enemy = new Enemy(pos, coin, 3);
                enemy->getEnemy().setScale(64.0f / 18.0f, 64.0f / 18.0f);
                this->enemiesMap.push_back(enemy);
                break;
            }
        }
    }
}

void Map::drawMap(sf::RenderWindow &window) {
    for (auto element : this->colliisonMap)
        element.draw(window);
}

const std::vector<Tile> &Map::getColliisonMap() const {
    return colliisonMap;
}

 std::vector<Enemy*> &Map::getEnemiesMap()  {
    return enemiesMap;
}