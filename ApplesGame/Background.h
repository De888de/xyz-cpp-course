#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Background
    {
        sf::RectangleShape sprite;

        void Init();
        void SetGameOverColor();
        void SetNormalColor();
    };
}



