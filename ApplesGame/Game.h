#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "GameTexts.h"
#include "Background.h"
#include "Leaderboard.h" 

namespace ApplesGame
{
    
    enum GameModeFlags
    {
        GAME_MODE_NONE = 0,
        GAME_MODE_INFINITE_APPLES = 1 << 0,
        GAME_MODE_WITH_ACCELERATION = 1 << 1,
        GAME_MODE_HIGH_SPEED = 1 << 2,
        GAME_MODE_50_APPLES = 1 << 3,
    };

    // Game States
    enum class GameStateType
    {
        SELECTING_MODE,
        PLAYING,
        GAME_OVER,
        CONFIRM_EXIT
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
        GameStateType previousState = GameStateType::SELECTING_MODE;

    
        unsigned int gameMode = GAME_MODE_WITH_ACCELERATION;

        // Texts for different states
        sf::Text modeSelectionText;
        sf::Text gameOverMenuText;
        sf::Text leaderboardText;
        sf::Text congratulationText;
        sf::Text exitConfirmText;

        // Leaderboard
        Leaderboard leaderboard; 

        //Resources
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatenApplesBuffer;
        sf::SoundBuffer brokenApplesBuffer;
        sf::Sound sound;

        sf::Music music;
    };

    // Main functions of the game
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

    // Auxiliary functions for updateGame
    void HandlePlayerInput(Game& game);
    void HandleAppleCollisions(Game& game);
    void HandleRockCollisions(Game& game);
    void HandleBorderCollisions(Game& game);
    void HandleGameOverInput(Game& game);
    void HandleExitConfirmation(Game& game, sf::RenderWindow& window);

    // Functions for initializing texts
    void InitModeSelectionText(Game& game);
    void InitGameOverMenuText(Game& game);
    void InitLeaderboardText(Game& game);
    void InitCongratulationText(Game& game);
    void InitExitConfirmText(Game& game);

    // The function of updating the greeting text
    void UpdateCongratulationText(Game& game);
}