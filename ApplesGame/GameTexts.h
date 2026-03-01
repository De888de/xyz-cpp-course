#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
    struct GameTexts
    {
        sf::Font font;
        sf::Text scoreText;
        sf::Text gameOverText;
        sf::Text restartText;

        void Init();
        void UpdateScore(int score);
    };

}


