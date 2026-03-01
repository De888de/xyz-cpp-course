#include "Game.h"
#include "Math.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace ApplesGame
{
    // Функции для работы с фоном
    void InitBackground(Game& game)
    {
        game.backgroundShape.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.backgroundShape.setFillColor(sf::Color::Black);
        game.backgroundShape.setPosition(0.f, 0.f);
    }

    void SetBackgroundGameOverColor(Game& game)
    {
        game.backgroundShape.setFillColor(sf::Color(100, 0, 0, 255)); // Темно-красный фон
    }

    void SetBackgroundNormalColor(Game& game)
    {
        game.backgroundShape.setFillColor(sf::Color::Black);
    }

    void InitModeSelectionText(Game& game)
    {
        game.modeSelectionText.setFont(game.texts.font);
        game.modeSelectionText.setCharacterSize(24);
        game.modeSelectionText.setFillColor(sf::Color::White);
        game.modeSelectionText.setString(
            "SELECT GAME MODE:\n\n"
            "1 - 20 apples, with acceleration\n"
            "2 - 20 apples, without acceleration\n"
            "3 - 50 apples, with acceleration\n"
            "4 - 20 apples, infinite apples, with acceleration\n"
            "5 - 20 apples, infinite apples, without acceleration\n"
            "6 - 50 apples, infinite apples, with acceleration\n"
            "7 - 50 apples, infinite apples, high speed, with acceleration\n\n"
            "Press 1-7 to select mode\n"
            "Press ESC to exit"
        );

        // Центрируем текст
        sf::FloatRect textRect = game.modeSelectionText.getLocalBounds();
        game.modeSelectionText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        game.modeSelectionText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
    }

    void InitGameOverMenuText(Game& game)
    {
        game.gameOverMenuText.setFont(game.texts.font);
        game.gameOverMenuText.setCharacterSize(30);
        game.gameOverMenuText.setFillColor(sf::Color::Yellow);
        game.gameOverMenuText.setString(
            "GAME OVER\n\n"
            "Press SPACE to play again\n"
            "Press M to return to menu\n"
            "Press ESC to exit"
        );

        // Центрируем текст
        sf::FloatRect textRect = game.gameOverMenuText.getLocalBounds();
        game.gameOverMenuText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        game.gameOverMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
    }

    void ApplyGameMode(Game& game)
    {
        // Определяем количество яблок по режиму
        if (HasGameMode(game, GAME_MODE_50_APPLES))
        {
            game.numApples = 50;
        }
        else
        {
            game.numApples = 20;
        }

        // Освобождаем старую память если есть
        if (game.apples != nullptr)
        {
            delete[] game.apples;
        }

        // Выделяем новую память
        game.apples = new Apple[game.numApples];

        // Инициализируем яблоки
        for (int i = 0; i < game.numApples; ++i)
        {
            game.apples[i].Init(game);
        }

        // Применяем режим высокой скорости
        if (HasGameMode(game, GAME_MODE_HIGH_SPEED))
        {
            game.player.speed = INITIAL_SPEED * 1.5f;
        }
        else
        {
            game.player.speed = INITIAL_SPEED;
        }

        std::cout << "Applied game mode with " << game.numApples << " apples" << std::endl;
    }

    void InitGame(Game& game)
    {
        // Загрузка текстур
        if (!game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"))
        {
            // Создаем простую текстуру если файл не найден
            sf::Image playerImage;
            playerImage.create(32, 32, sf::Color::Red);
            game.playerTexture.loadFromImage(playerImage);
        }

        if (!game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"))
        {
            sf::Image appleImage;
            appleImage.create(32, 32, sf::Color::Green);
            game.appleTexture.loadFromImage(appleImage);
        }

        if (!game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"))
        {
            sf::Image rockImage;
            rockImage.create(32, 32, sf::Color::Yellow);
            game.rockTexture.loadFromImage(rockImage);
        }

        // Загрузка звуков
        if (!game.eatenApplesBuffer.loadFromFile(RESOURCES_PATH + "EatApple.wav"))
        {
            // Если звук не загружен, просто продолжаем без звука
            std::cout << "Warning: Could not load EatApple.wav" << std::endl;
        }
        game.sound.setBuffer(game.eatenApplesBuffer);

        // Загрузка музыки
        if (!game.backgroundMusic.openFromFile(RESOURCES_PATH + "BackgroundMusic.ogg"))
        {
            std::cout << "Warning: Could not load BackgroundMusic.ogg" << std::endl;
        }
        else
        {
            game.backgroundMusic.setLoop(true);
            game.backgroundMusic.setVolume(50.f);
            game.backgroundMusic.play();
        }

        // Инициализация фона
        InitBackground(game);

        // Инициализация текстов
        game.texts.Init();

        // Инициализация текста выбора режима
        InitModeSelectionText(game);

        // Инициализация текста меню Game Over
        InitGameOverMenuText(game);

        // Инициализация игрока
        game.player.Init(game);

        // Инициализация камней (фиксированное количество)
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Init(game);
        }

        // Инициализация состояния игры
        game.score = 0;
        game.gameState = GameStateType::SELECTING_MODE;
        game.apples = nullptr; // Яблоки пока не инициализированы
        game.numApples = 0;
    }

    void DeinitializeGame(Game& game)
    {
        // Освобождаем память
        if (game.apples != nullptr)
        {
            delete[] game.apples;
            game.apples = nullptr;
        }
    }

    void SetGameMode(Game& game, unsigned int mode)
    {
        game.gameMode = mode;
    }

    bool HasGameMode(Game& game, unsigned int mode)
    {
        return (game.gameMode & mode) != 0;
    }

    void PrintGameModes(const Game& game)
    {
        std::cout << "Current game modes:" << std::endl;
        std::cout << "- Infinite apples: " << (HasGameMode(const_cast<Game&>(game), GAME_MODE_INFINITE_APPLES) ? "YES" : "NO") << std::endl;
        std::cout << "- With acceleration: " << (HasGameMode(const_cast<Game&>(game), GAME_MODE_WITH_ACCELERATION) ? "YES" : "NO") << std::endl;
        std::cout << "- High speed: " << (HasGameMode(const_cast<Game&>(game), GAME_MODE_HIGH_SPEED) ? "YES" : "NO") << std::endl;
        std::cout << "- 50 apples: " << (HasGameMode(const_cast<Game&>(game), GAME_MODE_50_APPLES) ? "YES" : "NO") << std::endl;
    }

    void ResetGame(Game& game)
    {
        // Reset background
        SetBackgroundNormalColor(game);

        // Reset player
        game.player.Reset();

        // Применяем режим игры заново
        ApplyGameMode(game);

        // Reset rocks
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Reset();
        }

        // Reset game state
        game.score = 0;
        game.texts.UpdateScore(0);
        game.gameState = GameStateType::PLAYING;

        std::cout << "Game reset" << std::endl;
    }

    void ReturnToMenu(Game& game)
    {
        // Освобождаем память от яблок
        if (game.apples != nullptr)
        {
            delete[] game.apples;
            game.apples = nullptr;
        }

        // Reset background
        SetBackgroundNormalColor(game);

        // Reset player
        game.player.Reset();

        // Reset rocks
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Reset();
        }

        // Reset game state
        game.score = 0;
        game.texts.UpdateScore(0);
        game.numApples = 0;
        game.gameState = GameStateType::SELECTING_MODE;

        std::cout << "Returned to menu" << std::endl;
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        // Ограничиваем deltaTime, чтобы избежать резких скачков
        if (deltaTime > 0.1f)
        {
            deltaTime = 0.1f;
        }

        // Обработка в зависимости от состояния игры
        if (game.gameState == GameStateType::SELECTING_MODE)
        {
            // Обработка выбора режима по цифровым клавишам
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                game.gameMode = GAME_MODE_WITH_ACCELERATION;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                game.gameMode = GAME_MODE_NONE;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_50_APPLES;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                game.gameMode = GAME_MODE_INFINITE_APPLES;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            {
                game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES | GAME_MODE_50_APPLES;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            {
                game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES | GAME_MODE_50_APPLES | GAME_MODE_HIGH_SPEED;
                ApplyGameMode(game);
                game.gameState = GameStateType::PLAYING;
            }
        }
        else if (game.gameState == GameStateType::PLAYING)
        {
            // Handle input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.player.direction = PlayerDirection::Right;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                game.player.direction = PlayerDirection::Up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                game.player.direction = PlayerDirection::Left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                game.player.direction = PlayerDirection::Down;
            }

            // Update player position
            game.player.UpdatePosition(deltaTime);

            // Collisions with apples
            for (int i = 0; i < game.numApples; ++i)
            {
                if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
                    game.apples[i].position, APPLE_SIZE / 2.f))
                {
                    // Воспроизводим звук
                    if (game.eatenApplesBuffer.getSampleCount() > 0)
                    {
                        game.sound.play();
                    }

                    if (HasGameMode(game, GAME_MODE_INFINITE_APPLES))
                    {
                        // Бесконечные яблоки - просто перемещаем
                        game.apples[i].Reset();
                    }
                    else
                    {
                        // Конечные яблоки - удаляем и сдвигаем массив
                        for (int j = i; j < game.numApples - 1; ++j)
                        {
                            game.apples[j] = game.apples[j + 1];
                        }
                        game.numApples--;
                        i--; // Проверяем тот же индекс с новым яблоком
                    }

                    game.score++;

                    // Ускорение если включен режим
                    if (HasGameMode(game, GAME_MODE_WITH_ACCELERATION))
                    {
                        game.player.speed += ACCELERATION;
                    }

                    game.texts.UpdateScore(game.score);

                    // Если яблоки кончились - игра завершена
                    if (!HasGameMode(game, GAME_MODE_INFINITE_APPLES) && game.numApples <= 0)
                    {
                        game.gameState = GameStateType::GAME_OVER;
                    }

                    break; // Выходим из цикла, чтобы не проверять дальше
                }
            }

            // Collisions with rocks
            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
                    game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
                {
                    game.gameState = GameStateType::GAME_OVER;
                }
            }

            // Screen borders collision
            if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f ||
                game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                game.player.position.y - PLAYER_SIZE / 2.f < 0.f ||
                game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
            {
                game.gameState = GameStateType::GAME_OVER;
            }
        }
        else if (game.gameState == GameStateType::GAME_OVER)
        {
            // Restart on space
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                ResetGame(game);
            }
            // Return to menu on M
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                ReturnToMenu(game);
            }
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.backgroundShape); // Рисуем фон

        if (game.gameState == GameStateType::SELECTING_MODE)
        {
            // Рисуем текст выбора режима
            window.draw(game.modeSelectionText);
        }
        else if (game.gameState == GameStateType::PLAYING)
        {
            window.draw(game.player.sprite);

            for (int i = 0; i < game.numApples; ++i)
            {
                window.draw(game.apples[i].sprite);
            }

            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                window.draw(game.rocks[i].sprite);
            }

            window.draw(game.texts.scoreText);
        }
        else if (game.gameState == GameStateType::GAME_OVER)
        {
            SetBackgroundGameOverColor(game); // Меняем цвет фона при Game Over
            window.draw(game.backgroundShape); // Перерисовываем фон с новым цветом

            window.draw(game.gameOverMenuText); // Рисуем меню Game Over
        }
    }
}