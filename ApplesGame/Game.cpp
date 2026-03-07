#include "Game.h"
#include "Math.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace ApplesGame
{
    // Инициализация текстов меню
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
            "Press SPACE to play again\n"
            "Press M to return to menu\n"
            "Press ESC to exit"
        );


    }

    void InitLeaderboardText(Game& game)
    {
        game.leaderboardText.setFont(game.texts.font);
        game.leaderboardText.setCharacterSize(20);
        game.leaderboardText.setFillColor(sf::Color::Cyan);
    }

    void InitCongratulationText(Game& game)
    {
        game.congratulationText.setFont(game.texts.font);
        game.congratulationText.setCharacterSize(28);
        game.congratulationText.setFillColor(sf::Color::Green);
        game.congratulationText.setStyle(sf::Text::Bold);
    }

    void UpdateCongratulationText(Game& game)
    {
        std::stringstream ss;
        ss << "Congratulations, you've scored " << game.score << " points!";
        game.congratulationText.setString(ss.str());


        sf::FloatRect textRect = game.congratulationText.getLocalBounds();
        game.congratulationText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        game.congratulationText.setPosition(SCREEN_WIDTH / 2.f, 80);
    }


    void SetGameMode(Game& game, unsigned int mode)
    {
        game.gameMode = mode;
    }

    bool HasGameMode(Game& game, unsigned int mode)
    {
        return (game.gameMode & mode) != 0;
    }

    void ApplyGameMode(Game& game)
    {

        if (HasGameMode(game, GAME_MODE_50_APPLES))
        {
            game.numApples = 50;
        }
        else
        {
            game.numApples = 20;
        }


        if (game.apples != nullptr)
        {
            delete[] game.apples;
        }


        game.apples = new Apple[game.numApples];


        for (int i = 0; i < game.numApples; ++i)
        {
            game.apples[i].Init(game);
        }


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

    void HandleModeSelection(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            game.gameMode = GAME_MODE_WITH_ACCELERATION;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            game.gameMode = GAME_MODE_NONE;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_50_APPLES;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            game.gameMode = GAME_MODE_INFINITE_APPLES;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES | GAME_MODE_50_APPLES;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        {
            game.gameMode = GAME_MODE_WITH_ACCELERATION | GAME_MODE_INFINITE_APPLES | GAME_MODE_50_APPLES | GAME_MODE_HIGH_SPEED;
            ApplyGameMode(game);
            GenerateLeaderboard(game);
            game.gameState = GameStateType::PLAYING;
        }
    }


    void SortLeaderboard(std::vector<LeaderboardEntry>& leaderboard)
    {

        for (size_t i = 0; i < leaderboard.size() - 1; ++i)
        {
            for (size_t j = 0; j < leaderboard.size() - i - 1; ++j)
            {
                if (leaderboard[j].score < leaderboard[j + 1].score)
                {

                    LeaderboardEntry temp = leaderboard[j];
                    leaderboard[j] = leaderboard[j + 1];
                    leaderboard[j + 1] = temp;
                }
            }
        }
    }

    void GenerateLeaderboard(Game& game)
    {
        game.leaderboard.clear();


        std::vector<std::string> names = { "Alice", "Bob", "Carol", "Dave", "Eve", "Frank", "Grace", "Henry", "Ivy", "Jack" };
        std::vector<int> scores = { 120, 85, 55, 30, 150, 95, 70, 45, 110, 65 };


        for (size_t i = 0; i < names.size(); ++i)
        {
            LeaderboardEntry entry;
            entry.name = names[i];
            entry.score = scores[i];
            game.leaderboard.push_back(entry);
        }


        LeaderboardEntry playerEntry;
        playerEntry.name = game.playerName;
        playerEntry.score = 0;
        game.leaderboard.push_back(playerEntry);


        SortLeaderboard(game.leaderboard);
    }

    void UpdateLeaderboard(Game& game)
    {

        for (auto& entry : game.leaderboard)
        {
            if (entry.name == game.playerName)
            {
                entry.score = game.score;
                break;
            }
        }


        SortLeaderboard(game.leaderboard);
    }

    std::string FormatLeaderboard(const Game& game)
    {
        std::stringstream ss;
        ss << "===== LEADERBOARD =====\n\n";

        int count = 0;
        for (const auto& entry : game.leaderboard)
        {
            if (count >= 5) break;

            ss << count + 1 << ". " << entry.name;


            int dotsCount = 20 - entry.name.length() - std::to_string(entry.score).length();
            for (int i = 0; i < dotsCount; ++i)
            {
                ss << ".";
            }

            ss << " " << entry.score << "\n";
            count++;
        }

        ss << "\n=======================";
        return ss.str();
    }


    void InitGame(Game& game)
    {

        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
        assert(game.eatenApplesBuffer.loadFromFile(RESOURCES_PATH + "apple_eat.wav"));
        assert(game.brokenApplesBuffer.loadFromFile(RESOURCES_PATH + "game_over.wav"));


        game.music.openFromFile(RESOURCES_PATH + "background_music.ogg");
        game.music.setLoop(true);
        game.music.play();


        game.background.Init();
        game.texts.Init();
        game.player.Init(game);


        InitModeSelectionText(game);
        InitGameOverMenuText(game);
        InitLeaderboardText(game);
        InitCongratulationText(game);


        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Init(game);
        }


        game.score = 0;
        game.gameState = GameStateType::SELECTING_MODE;
        game.apples = nullptr;
        game.numApples = 0;
    }

    void ResetGame(Game& game)
    {
        game.background.SetNormalColor();
        game.player.Reset();


        ApplyGameMode(game);


        UpdateLeaderboard(game);

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Reset();
        }

        game.score = 0;
        game.texts.UpdateScore(0);
        game.gameState = GameStateType::PLAYING;
    }

    void ReturnToMenu(Game& game)
    {
        if (game.apples != nullptr)
        {
            delete[] game.apples;
            game.apples = nullptr;
        }

        game.background.SetNormalColor();
        game.player.Reset();

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            game.rocks[i].Reset();
        }

        game.score = 0;
        game.texts.UpdateScore(0);
        game.numApples = 0;
        game.gameState = GameStateType::SELECTING_MODE;
    }


    void HandlePlayerInput(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.player.direction = PlayerDirection::Right;
            game.player.sprite.setRotation(0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game.player.direction = PlayerDirection::Up;
            game.player.sprite.setRotation(-90.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.player.direction = PlayerDirection::Left;
            game.player.sprite.setRotation(0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game.player.direction = PlayerDirection::Down;
            game.player.sprite.setRotation(90.f);
        }
    }

    void HandleAppleCollisions(Game& game)
    {
        for (int i = 0; i < game.numApples; ++i)
        {
            if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
                game.apples[i].position, APPLE_SIZE / 2.f))
            {

                game.sound.setBuffer(game.eatenApplesBuffer);
                game.sound.play();

                if (HasGameMode(game, GAME_MODE_INFINITE_APPLES))
                {
                    game.apples[i].Reset();
                }
                else
                {

                    for (int j = i; j < game.numApples - 1; ++j)
                    {
                        game.apples[j] = game.apples[j + 1];
                    }
                    game.numApples--;
                    i--;
                }

                game.score++;

                if (HasGameMode(game, GAME_MODE_WITH_ACCELERATION))
                {
                    game.player.speed += ACCELERATION;
                }

                game.texts.UpdateScore(game.score);

                if (!HasGameMode(game, GAME_MODE_INFINITE_APPLES) && game.numApples <= 0)
                {

                    UpdateLeaderboard(game);
                    game.gameState = GameStateType::GAME_OVER;
                }

                break;
            }
        }
    }

    void HandleRockCollisions(Game& game)
    {
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
                game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
            {
                game.sound.setBuffer(game.brokenApplesBuffer);
                game.sound.play();

                UpdateLeaderboard(game);
                game.gameState = GameStateType::GAME_OVER;
            }
        }
    }

    void HandleBorderCollisions(Game& game)
    {
        if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f ||
            game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
            game.player.position.y - PLAYER_SIZE / 2.f < 0.f ||
            game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
        {
            game.sound.setBuffer(game.brokenApplesBuffer);
            game.sound.play();

            UpdateLeaderboard(game);
            game.gameState = GameStateType::GAME_OVER;
        }
    }

    void HandleGameOverInput(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            ResetGame(game);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            ReturnToMenu(game);
        }
    }


    void UpdateGame(Game& game, float deltaTime)
    {
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        switch (game.gameState)
        {
        case GameStateType::SELECTING_MODE:
            HandleModeSelection(game);
            break;

        case GameStateType::PLAYING:
            HandlePlayerInput(game);
            game.player.UpdatePosition(deltaTime);
            HandleAppleCollisions(game);
            HandleRockCollisions(game);
            HandleBorderCollisions(game);
            break;

        case GameStateType::GAME_OVER:
            HandleGameOverInput(game);
            break;
        }
    }


    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background.sprite);

        switch (game.gameState)
        {
        case GameStateType::SELECTING_MODE:
            window.draw(game.modeSelectionText);
            break;

        case GameStateType::PLAYING:
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
            break;

        case GameStateType::GAME_OVER:
            game.background.SetGameOverColor();
            window.draw(game.background.sprite);


            UpdateCongratulationText(game);
            window.draw(game.congratulationText);


            game.leaderboardText.setString(FormatLeaderboard(game));


            sf::FloatRect leaderboardRect = game.leaderboardText.getLocalBounds();
            game.leaderboardText.setOrigin(leaderboardRect.left + leaderboardRect.width / 2.0f,
                leaderboardRect.top + leaderboardRect.height / 2.0f);
            game.leaderboardText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 40);

            window.draw(game.leaderboardText);


            sf::FloatRect menuRect = game.gameOverMenuText.getLocalBounds();
            game.gameOverMenuText.setOrigin(menuRect.left + menuRect.width / 2.0f,
                menuRect.top + menuRect.height / 2.0f);
            game.gameOverMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 120);

            window.draw(game.gameOverMenuText);
            break;
        }
    }

    void DeinitializeGame(Game& game)
    {
        if (game.apples != nullptr)
        {
            delete[] game.apples;
            game.apples = nullptr;
        }
    }
}