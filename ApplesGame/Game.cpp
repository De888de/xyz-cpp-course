#include "Game.h"
#include "Math.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace ApplesGame
{
    // Initialization of menu texts
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

    void InitExitConfirmText(Game& game)
    {
        game.exitConfirmText.setFont(game.texts.font);
        game.exitConfirmText.setCharacterSize(20);
        game.exitConfirmText.setFillColor(sf::Color::White);
        game.exitConfirmText.setStyle(sf::Text::Bold);
        game.exitConfirmText.setString(
            "Are you sure you want to exit?\n\n"
            "Y - Yes, exit the game\n"
            "N - No, return to game"
        );

        sf::FloatRect textRect = game.exitConfirmText.getLocalBounds();
        game.exitConfirmText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        game.exitConfirmText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
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

    // Functions for working with modes
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
        // We determine the number of apples
        int numApples = HasGameMode(game, GAME_MODE_50_APPLES) ? 50 : 20;

        // We clean and fill the vector of apples
        game.apples.clear();
        game.apples.reserve(numApples);

        for (int i = 0; i < numApples; ++i)
        {
            Apple apple;
            apple.Init(game);
            game.apples.push_back(apple);
        }

        // Applying speed
        if (HasGameMode(game, GAME_MODE_HIGH_SPEED))
        {
            game.player.speed = INITIAL_SPEED * 1.5f;
        }
        else
        {
            game.player.speed = INITIAL_SPEED;
        }

        std::cout << "Applied game mode with " << game.apples.size() << " apples" << std::endl;
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            game.previousState = game.gameState;
            game.gameState = GameStateType::CONFIRM_EXIT;
        }
    }

    // Functions for working with the leaderboard
    void SortLeaderboard(std::vector<LeaderboardEntry>& leaderboard)
    {
        for (size_t i = 0; i < leaderboard.size() - 1; ++i)
        {
            for (size_t j = 0; j < leaderboard.size() - i - 1; ++j)
            {
                if (leaderboard[j].score < leaderboard[j + 1].score)
                {
                    std::swap(leaderboard[j], leaderboard[j + 1]);
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

            int dotsCount = 20 - static_cast<int>(entry.name.length()) - static_cast<int>(std::to_string(entry.score).length());
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

    // Basic initialization of the game
    void InitGame(Game& game)
    {
        // Loading resources
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
        assert(game.eatenApplesBuffer.loadFromFile(RESOURCES_PATH + "apple_eat.wav"));
        assert(game.brokenApplesBuffer.loadFromFile(RESOURCES_PATH + "game_over.wav"));

        // Music
        game.music.openFromFile(RESOURCES_PATH + "background_music.ogg");
        game.music.setLoop(true);
        game.music.play();

        // Initializing components
        game.background.Init();
        game.texts.Init();
        game.player.Init(game);

        // Initialization of menu texts
        InitModeSelectionText(game);
        InitGameOverMenuText(game);
        InitLeaderboardText(game);
        InitCongratulationText(game);
        InitExitConfirmText(game);

        // Initialization of stones (vector)
        game.rocks.clear();
        game.rocks.reserve(NUM_ROCKS);

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            Rock rock;
            rock.Init(game);
            game.rocks.push_back(rock);
        }

        // Initial state
        game.score = 0;
        game.gameState = GameStateType::SELECTING_MODE;
        game.apples.clear();
    }

    void ResetGame(Game& game)
    {
        game.background.SetNormalColor();
        game.player.Reset();

        // Applying the mode again
        ApplyGameMode(game);

        // Updating the leaderboard
        UpdateLeaderboard(game);

        // Dropping the stones
        for (auto& rock : game.rocks)
        {
            rock.Reset();
        }

        game.score = 0;
        game.texts.UpdateScore(0);
        game.gameState = GameStateType::PLAYING;
    }

    void ReturnToMenu(Game& game)
    {
        game.apples.clear();
        game.background.SetNormalColor();
        game.player.Reset();

        for (auto& rock : game.rocks)
        {
            rock.Reset();
        }

        game.score = 0;
        game.texts.UpdateScore(0);
        game.gameState = GameStateType::SELECTING_MODE;
    }

    // Game Features
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
        for (auto it = game.apples.begin(); it != game.apples.end(); )
        {
            if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
                it->position, APPLE_SIZE / 2.f))
            {
                // The sound of eating
                game.sound.setBuffer(game.eatenApplesBuffer);
                game.sound.play();

                if (HasGameMode(game, GAME_MODE_INFINITE_APPLES))
                {
                    it->Reset();
                    ++it;
                }
                else
                {
                    it = game.apples.erase(it);
                }

                game.score++;

                if (HasGameMode(game, GAME_MODE_WITH_ACCELERATION))
                {
                    game.player.speed += ACCELERATION;
                }

                game.texts.UpdateScore(game.score);

                if (!HasGameMode(game, GAME_MODE_INFINITE_APPLES) && game.apples.empty())
                {
                    UpdateLeaderboard(game);
                    game.gameState = GameStateType::GAME_OVER;
                }

                if (!HasGameMode(game, GAME_MODE_INFINITE_APPLES))
                {
                    break;
                }
            }
            else
            {
                ++it;
            }
        }
    }

    void HandleRockCollisions(Game& game)
    {
        for (const auto& rock : game.rocks)
        {
            if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
                rock.position, { ROCK_SIZE, ROCK_SIZE }))
            {
                game.sound.setBuffer(game.brokenApplesBuffer);
                game.sound.play();
                UpdateLeaderboard(game);
                game.gameState = GameStateType::GAME_OVER;
                break;
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            game.previousState = game.gameState;
            game.gameState = GameStateType::CONFIRM_EXIT;
        }
    }

    void HandleExitConfirmation(Game& game, sf::RenderWindow& window)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            window.close(); // Exit the game
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            game.gameState = game.previousState; // Return to the previous state
        }
    }

    // Main update function
    void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window)
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

            // We check ESC during the game
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                game.previousState = game.gameState;
                game.gameState = GameStateType::CONFIRM_EXIT;
            }
            break;

        case GameStateType::GAME_OVER:
            HandleGameOverInput(game);
            break;

        case GameStateType::CONFIRM_EXIT:
            HandleExitConfirmation(game, window);
            break;
        }
    }

    // The rendering function
    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background.sprite);

        // Declaring variables in advance
        sf::FloatRect leaderboardRect;
        sf::FloatRect menuRect;

        switch (game.gameState)
        {
        case GameStateType::SELECTING_MODE:
        {
            window.draw(game.modeSelectionText);
            break;
        }

        case GameStateType::PLAYING:
        {
            window.draw(game.player.sprite);

            for (const auto& apple : game.apples)
            {
                window.draw(apple.sprite);
            }

            for (const auto& rock : game.rocks)
            {
                window.draw(rock.sprite);
            }

            window.draw(game.texts.scoreText);
            break;
        }

        case GameStateType::GAME_OVER:
        {
            game.background.SetGameOverColor();
            window.draw(game.background.sprite);

            UpdateCongratulationText(game);
            window.draw(game.congratulationText);

            game.leaderboardText.setString(FormatLeaderboard(game));

            leaderboardRect = game.leaderboardText.getLocalBounds();
            game.leaderboardText.setOrigin(leaderboardRect.left + leaderboardRect.width / 2.0f,
                leaderboardRect.top + leaderboardRect.height / 2.0f);
            game.leaderboardText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 40);

            window.draw(game.leaderboardText);

            menuRect = game.gameOverMenuText.getLocalBounds();
            game.gameOverMenuText.setOrigin(menuRect.left + menuRect.width / 2.0f,
                menuRect.top + menuRect.height / 2.0f);
            game.gameOverMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 120);

            window.draw(game.gameOverMenuText);
            break;
        }

        case GameStateType::CONFIRM_EXIT:
        {
            // Darken the background
            sf::RectangleShape darkOverlay;
            darkOverlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
            darkOverlay.setFillColor(sf::Color(0, 0, 0, 200));
            window.draw(darkOverlay);

            // Drawing a dialog on top of
            window.draw(game.exitConfirmText);
            break;
        }
        }
    }

    void DeinitializeGame(Game& game)
    {
        game.apples.clear();
        game.rocks.clear();
        game.leaderboard.clear();
    }
} 