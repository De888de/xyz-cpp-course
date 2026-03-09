#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "GameTexts.h"
#include "Background.h"
#include <SFML/Audio.hpp>

namespace ApplesGame
{
    // Bit flags for game modes
    enum GameModeFlags
    {
        GAME_MODE_NONE = 0,
        GAME_MODE_INFINITE_APPLES = 1 << 0,      // 1 - endless apples
        GAME_MODE_WITH_ACCELERATION = 1 << 1,     // 2 - with acceleration
        GAME_MODE_HIGH_SPEED = 1 << 2,            // 4 - high speed
        GAME_MODE_50_APPLES = 1 << 3,             // 8 - 50 яблок
    };

    // Game States
    enum class GameStateType
    {
        SELECTING_MODE,  // Mode selection
        PLAYING,         // Game
        GAME_OVER,       // End of the game
        CONFIRM_EXIT     // Confirmation dialog for exit (new state)
    };

    // The structure for the record in the high score table
    struct LeaderboardEntry
    {
        std::string name;
        int score;
    };

    struct Game
    {
        Player player;
        std::vector<Apple> apples;
        std::vector<Rock> rocks;
        GameTexts texts;
        Background background;

        int score = 0;
        GameStateType gameState = GameStateType::SELECTING_MODE;
        GameStateType previousState = GameStateType::SELECTING_MODE; // To return after the dialog

        // Game mode (bitmask)
        unsigned int gameMode = GAME_MODE_WITH_ACCELERATION;

        // Тексты для разных состояний
        sf::Text modeSelectionText;
        sf::Text gameOverMenuText;
        sf::Text leaderboardText;
        sf::Text congratulationText;
        sf::Text exitConfirmText;  // New text for the exit dialog

        // Leaderboard
        std::vector<LeaderboardEntry> leaderboard;
        std::string playerName = "Player";

        //Resources
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatenApplesBuffer;
        sf::SoundBuffer brokenApplesBuffer;
        sf::Sound sound;

        sf::Music music;
    };

    // The main functions of the game
    void InitGame(Game& game);
    void ResetGame(Game& game);
    void ReturnToMenu(Game& game);
    void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinitializeGame(Game& game);

    // Functions for working with modes
    void SetGameMode(Game& game, unsigned int mode);
    bool HasGameMode(Game& game, unsigned int mode);
    void ApplyGameMode(Game& game);
    void HandleModeSelection(Game& game);

    // Auxiliary functions for UpdateGame
    void HandlePlayerInput(Game& game);
    void HandleAppleCollisions(Game& game);
    void HandleRockCollisions(Game& game);
    void HandleBorderCollisions(Game& game);
    void HandleGameOverInput(Game& game);
    void HandleExitConfirmation(Game& game, sf::RenderWindow& window); // New Function

    // Functions for initializing texts
    void InitModeSelectionText(Game& game);
    void InitGameOverMenuText(Game& game);
    void InitLeaderboardText(Game& game);
    void InitCongratulationText(Game& game);
    void InitExitConfirmText(Game& game); // New Function

    // Functions for working with the leaderboard
    void GenerateLeaderboard(Game& game);
    void UpdateLeaderboard(Game& game);
    void SortLeaderboard(std::vector<LeaderboardEntry>& leaderboard);
    std::string FormatLeaderboard(const Game& game);
    void UpdateCongratulationText(Game& game);
}