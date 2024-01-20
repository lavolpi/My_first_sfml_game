//
// Created by barto on 29.12.2023.
//

#include "Player.h"
#include "fmt/core.h"


Player::Player(sf::Vector2f &position, sf::Texture &texture) : velocity(350.f), jumpVelocity(475.f),
collisionLeft(false), collisionRight(false), canJump(false), gravity(230.f), isOnGround(false),gameOver(false), jumpUpgrade(0), moveSpeedUpgrade(0), immortalUpgrade(0), immortal(false)
{
    this->player.setPosition(position);
    this->player.setTexture(texture);
    this->player.setScale(48.0f / 24.0f, 48.0f / 24.0f);
}

void Player::move(sf::Vector2f &offset)
{
    player.move(offset);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(this->player);
}

void Player::update(sf::RenderWindow &window, const float &dt)
{
    this->movement = sf::Vector2f(0.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !collisionLeft)
    {
        this->moveLeft(dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !collisionRight)
    {
        this->moveRight(dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
    {
        this->jump();
    }
    if(!canJump)
    {
        this->movement.y -= jumpVelocity*dt;
        jumpVelocity -= 350.f*dt;
    }
    if(!this->isOnGround)
    {
        this->movement.y += gravity*dt; //grawitacja
    }
    else
    {
        this->movement.y = 0.f;
        this->canJump = true;
        if(this->jumpUpgrade < 5)
        {
            this->jumpVelocity = 475.f;
        }
        else
        {
            this->jumpVelocity = 600.f;
        }
    }
    if(this->immortalUpgrade >=3){this->immortal = true;}
    if(this->getMoveSpeedUpgrade()>=5){this->velocity = 500.f;}
    this->move(this->movement);
    this->draw(window);
}

void Player::jump()
{
    if(this->isOnGround)
    {
        this->canJump = false;
        this->isOnGround = false;
    }

}

void Player::collision(const std::vector<Tile> &tiles, std::vector<Enemy*> &enemies, sf::RenderWindow &window) {
    //Obecna pozycja gracza
    sf::Vector2f playerPosition = player.getPosition();

    //Collision box gracza
    sf::FloatRect currentPlayerBounds(playerPosition, player.getGlobalBounds().getSize());

    for(Tile tile : tiles){
        if (currentPlayerBounds.intersects(tile.getTile().getGlobalBounds()) && tile.getIsCollidable())
        {
            // Kolizja z prawej strony
            if (movement.x > 0 && currentPlayerBounds.left < tile.getTile().getGlobalBounds().left)
            {
                // Collision from the right
                this->collisionRight = true;
                fmt::println("Prawo");
                player.setPosition(tile.getTile().getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
            }
                // Kolizja z lewej strony gracza
            else if (movement.x < 0 && currentPlayerBounds.left + currentPlayerBounds.width > tile.getTile().getGlobalBounds().left + tile.getTile().getGlobalBounds().width)
            {
                this->collisionLeft = true;
                fmt::println("Lewo");
                player.setPosition(tile.getTile().getGlobalBounds().left + tile.getTile().getGlobalBounds().width, player.getPosition().y);
            }
        }
        else if(currentPlayerBounds.intersects(tile.getTile().getGlobalBounds()) && tile.isDeadly1()  && !this->isImmortal())
        {
            this->gameOver = true;
        }
        else
        {
            this->collisionLeft = false;
            this->collisionRight = false;
        }

        sf::Vector2f playerBottomPosition = sf::Vector2f ({player.getPosition().x, player.getPosition().y+1});
        sf::FloatRect bottomCollisionBox(playerBottomPosition, player.getGlobalBounds().getSize());

        this->isOnGround = false; // Ustawiamy domyślnie na false

        if(bottomCollisionBox.intersects(tile.getTile().getGlobalBounds()) && tile.getIsCollidable() && playerBottomPosition.y <= tile.getTile().getGlobalBounds().top)
        {
            this->isOnGround = true;
            break; // Jeśli znaleźliśmy kolizyjny kafelek, na którym gracz jest, przerywamy pętlę
        }

    }

    sf::Vector2f playerBottomPosition = sf::Vector2f ({player.getPosition().x, player.getPosition().y+1});
    sf::FloatRect bottomCollisionBox(playerBottomPosition, player.getGlobalBounds().getSize());
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        if (bottomCollisionBox.intersects((*it)->getEnemy().getGlobalBounds()) && movement.y > 0)
        {
            if((*it)->getEnemyType() == 1)
            {
                if(this->moveSpeedUpgrade < 5)
                {
                    this->moveSpeedUpgrade++;
                }
            }
            else if ((*it)->getEnemyType() == 2)
            {
                if(this->jumpUpgrade < 5)
                {
                    this->jumpUpgrade++;
                }
            }
            else if ((*it)->getEnemyType() == 3)
            {
                if(this->immortalUpgrade < 3)
                {
                    this->immortalUpgrade++;
                }
            }
            enemies.erase(it);
            fmt::println("jump upgrade: {} movespeed upgrade: {} imortality upgrade: {}", this->jumpUpgrade, this->moveSpeedUpgrade, this->immortalUpgrade);
        }
        else if (bottomCollisionBox.intersects((*it)->getEnemy().getGlobalBounds()) && movement.y <= 0 && !this->isImmortal() && (*it)->getEnemyType()!=3)
        {
            //zakonczenie gry przez wyjscie z programu
            this->gameOver = true;
            fmt::println("xd");
         ++it;
        }
        else
        {
            ++it;
        }
    }

}

void Player::moveLeft(const float &dt)
{
    this->movement.x -= this->velocity*dt;
}

void Player::moveRight(const float &dt)
{
    this->movement.x += this->velocity*dt;
}

sf::Sprite Player::getPlayer()
{
    return this->player;
}

int Player::getJumpUpgrade() const {
    return jumpUpgrade;
}

int Player::getMoveSpeedUpgrade() const {
    return moveSpeedUpgrade;
}

bool Player::isGameOver(){
    return gameOver;
}

bool Player::isImmortal(){
    return immortal;
}

void Player::setImmortal(bool immortal){
    Player::immortal = immortal;
}

int Player::getImmortalUpgrade(){
    return immortalUpgrade;
}
