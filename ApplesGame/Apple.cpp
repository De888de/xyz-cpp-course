#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
    void Apple::Init(const Game& game)
    {
        position = GetRandomPositionInScreen();

        sprite.setTexture(game.appleTexture);
        SetSpriteSize(sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position.x, position.y);
    }

    void Apple::Reset()
    {
        position = GetRandomPositionInScreen();
        sprite.setPosition(position.x, position.y);
    }
}

