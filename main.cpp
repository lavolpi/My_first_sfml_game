#include <iostream>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include "Enemy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1024,768), "Moja gra", sf::Style::Close|sf::Style::Titlebar);
    sf::Clock clock;
    auto playerPos = sf::Vector2f(200, 650);

    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("playerTexture.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }
    Player player(playerPos, playerTexture);

    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("groundEnemy.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }
    sf::Texture bat;
    if(!bat.loadFromFile("bat.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }

    sf::View view(sf::FloatRect(0, 0, 1024, 768));
    Map map;

    sf::Texture grass;
    if(!grass.loadFromFile("grass.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }
    sf::Texture background;
    if(!background.loadFromFile("background.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }
    sf::Texture shroom;
    if(!shroom.loadFromFile("shroom.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }
    sf::Texture coin;
    if(!coin.loadFromFile("coin.png"))
    {
        fmt::println("Nie udało się załadować pliku");
        std::exit(EXIT_FAILURE);
    }

    sf::Font font;
    if(!font.loadFromFile("arial_bold.ttf"))
    {
        fmt::println("Nie udało się załadować czcionki");
        std::exit(EXIT_FAILURE);
    }


    map.initiateMap(background, grass, shroom, enemyTexture, bat, coin);

    while (window.isOpen())
    {
        auto tekst = "Upgrade skoku: " + std::to_string(player.getJumpUpgrade()) + "/5 | upgrade movespeeda: " + std::to_string(player.getMoveSpeedUpgrade()) + "/5 | niesmiertelnosc: " + std::to_string(player.getImmortalUpgrade()) + "/3" ;
        sf::Text text (tekst, font, 20);
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        if(!player.isGameOver())
        {
            view.setCenter(player.getPlayer().getPosition().x, window.getSize().y/2);
            window.setView(view);
            map.drawMap(window);
            player.collision(map.getColliisonMap(), (map.getEnemiesMap()), window);
            player.update(window, dt);
            for (auto &e : map.getEnemiesMap())
            {
                e->update(window, dt);
            }
            text.setPosition(view.getCenter().x + view.getSize().x /2 - text.getLocalBounds().width, view.getCenter().y - view.getSize().y /2);
            window.draw(text);
        }
        else
        {
            sf::Text gameOver("Game over", font, 50);
            gameOver.setPosition(view.getCenter().x - gameOver.getLocalBounds().width / 2,view.getCenter().y - gameOver.getLocalBounds().height / 2);
            window.draw(gameOver);
        }
        window.display();
    }
    return 0;
}