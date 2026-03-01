#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
    void Rock::Init(const Game& game)
    {
        position = GetRandomPositionInScreen();

        sprite.setTexture(game.rockTexture);
        SetSpriteSize(sprite, ROCK_SIZE, ROCK_SIZE);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position.x, position.y);
    }

    void Rock::Reset()
    {
        position = GetRandomPositionInScreen();
        sprite.setPosition(position.x, position.y);
    }
}