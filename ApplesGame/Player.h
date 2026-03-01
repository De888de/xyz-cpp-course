#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    // Предварительное объявление структуры Game
    struct Game;

    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = 0;
        PlayerDirection direction = PlayerDirection::Right; // Инициализируем здесь!
        sf::Sprite sprite;

        void Init(const Game& game);
        void Reset();
        void UpdatePosition(float deltaTime);
    };
}