#pragma once
#include <iostream>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "GameTexts.h"
#include <SFML/Audio.hpp>

namespace ApplesGame
{
    // Битовые флаги для режимов игры
    enum GameModeFlags
    {
        GAME_MODE_NONE = 0,
        GAME_MODE_INFINITE_APPLES = 1 << 0,      // 1 - бесконечные яблоки
        GAME_MODE_WITH_ACCELERATION = 1 << 1,     // 2 - с ускорением
        GAME_MODE_HIGH_SPEED = 1 << 2,            // 4 - высокая скорость
        GAME_MODE_50_APPLES = 1 << 3,             // 8 - 50 яблок
    };

    // Состояния игры
    enum class GameStateType
    {
        SELECTING_MODE,  // Выбор режима
        PLAYING,         // Игра
        GAME_OVER        // Конец игры
    };

    struct Game
    {
        Player player;
        Apple* apples = nullptr;  // Динамический массив
        int numApples = 0;         // Текущее количество яблок
        Rock rocks[NUM_ROCKS];
        GameTexts texts;

        // Фон
        sf::RectangleShape backgroundShape;

        int score = 0;
        GameStateType gameState = GameStateType::SELECTING_MODE; // Состояние игры

        // Режим игры (битовая маска)
        unsigned int gameMode = GAME_MODE_WITH_ACCELERATION; // По умолчанию с ускорением

        // Тексты для разных состояний
        sf::Text modeSelectionText;
        sf::Text gameOverMenuText;  // Текст в меню Game Over

        //Resources
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatenApplesBuffer;
        sf::Sound sound;

        sf::Music backgroundMusic;
    };

    // Декларации функций
    void InitGame(Game& game);
    void ResetGame(Game& game);
    void ReturnToMenu(Game& game);  // Новая функция для возврата в меню
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinitializeGame(Game& game);

    // Функции для работы с режимами
    void SetGameMode(Game& game, unsigned int mode);
    bool HasGameMode(Game& game, unsigned int mode);
    void PrintGameModes(const Game& game);
    void ApplyGameMode(Game& game); // Применяет выбранный режим

    // Функции для работы с фоном
    void InitBackground(Game& game);
    void SetBackgroundGameOverColor(Game& game);
    void SetBackgroundNormalColor(Game& game);

    // Функции для инициализации текстов
    void InitModeSelectionText(Game& game);
    void InitGameOverMenuText(Game& game); // Новая функция
}