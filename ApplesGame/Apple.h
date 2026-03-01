#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    // Предварительное объявление структуры Game
    struct Game;

    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;

        void Init(const Game& game);
        void Reset();
    };
}



