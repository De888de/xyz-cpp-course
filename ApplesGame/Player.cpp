#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
    void Player::Init(const Game& game)
    {
        position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        speed = INITIAL_SPEED;
        direction = PlayerDirection::Right;

        // Init player sprite
        sprite.setTexture(game.playerTexture);
        SetSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setPosition(position.x, position.y); // Важно! Устанавливаем позицию
    }

    void Player::Reset()
    {
        position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        speed = INITIAL_SPEED;
        direction = PlayerDirection::Right;
        sprite.setPosition(position.x, position.y);
    }

    void Player::UpdatePosition(float deltaTime)
    {
        const float baseScaleX = fabs(sprite.getScale().x);
        const float baseScaleY = sprite.getScale().y;

        switch (direction)
        {
        case PlayerDirection::Right:
            position.x += speed * deltaTime;
            sprite.setScale(baseScaleX, baseScaleY);
            break;
        case PlayerDirection::Up:
            position.y -= speed * deltaTime;
            sprite.setScale(baseScaleX, baseScaleY);
            break;
        case PlayerDirection::Left:
            position.x -= speed * deltaTime;
            sprite.setScale(-baseScaleX, baseScaleY); // зеркалим при повороте налево
            break;
        case PlayerDirection::Down:
            position.y += speed * deltaTime;
            sprite.setScale(baseScaleX, baseScaleY);
            break;
        }

        // Обновляем позицию спрайта
        sprite.setPosition(position.x, position.y);
    }
}