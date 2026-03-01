#include "GameTexts.h"
#include "Constants.h"

namespace ApplesGame
{
    void GameTexts::Init()
    {
        // Загрузка шрифта
        if (!font.loadFromFile("arial.ttf"))
        {
            font.loadFromFile("C:/Windows/Fonts/arial.ttf");
        }

        // Инициализация текста счета
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString("Score: 0");
        scoreText.setPosition(SCREEN_WIDTH - 150, 10);

        // Инициализация текста Game Over
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("GAME OVER");
        gameOverText.setStyle(sf::Text::Bold);

        // Центрирование текста Game Over
        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        gameOverText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 50));

        // Инициализация текста подсказки рестарта
        restartText.setFont(font);
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::Yellow);
        restartText.setString("Press SPACE to restart");
        restartText.setStyle(sf::Text::Bold);

        // Центрирование текста подсказки рестарта
        sf::FloatRect restartTextRect = restartText.getLocalBounds();
        restartText.setOrigin(restartTextRect.left + restartTextRect.width / 2.0f,
            restartTextRect.top + restartTextRect.height / 2.0f);
        restartText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 30));
    }

    void GameTexts::UpdateScore(int score)
    {
        scoreText.setString("Score: " + std::to_string(score));
    }
}

