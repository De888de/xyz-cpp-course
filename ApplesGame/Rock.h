#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame

{
    
    struct Game;

    struct Rock
    {
        Position2D position;
        sf::Sprite sprite;
        

        void Init(const Game& game);
        void Reset();
    };
}



