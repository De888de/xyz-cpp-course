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

    // Init window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

    // Game initialization
    Game game;
    InitGame(game);

    // Init game clocks
    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    // Main loop
    while (window.isOpen())
    {
        // Calculate time delta
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Read events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        // Update game with window parameter
        UpdateGame(game, deltaTime, window); 

        // Draw game
        window.clear();
        DrawGame(game, window);
        window.display();
    }

    // Deinitialization
    DeinitializeGame(game);

    return 0;
}