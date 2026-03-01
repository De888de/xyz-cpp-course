#include "Background.h"
#include "Constants.h"

namespace ApplesGame
{
    void Background::Init()
    {
        sprite.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        sprite.setFillColor(sf::Color::Black);
        sprite.setPosition(0.f, 0.f);
    }

    void Background::SetGameOverColor()
    {
        sprite.setFillColor(sf::Color(100, 0, 0, 255)); // Темно-красный фон во время Game Over
    }

    void Background::SetNormalColor()
    {
        sprite.setFillColor(sf::Color::Black);
    }
}

