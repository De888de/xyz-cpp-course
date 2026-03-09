#include "Game.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <SFML/Audio.hpp>

int main()
{
    using namespace ApplesGame;

    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

    Game game;
    InitGame(game);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        UpdateGame(game, deltaTime, window);

        window.clear();
        DrawGame(game, window);
        window.display();
    }

    DeinitializeGame(game);

    return 0;
}