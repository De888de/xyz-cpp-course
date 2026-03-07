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

    enum GameModeFlags
    {
        GAME_MODE_NONE = 0,
        GAME_MODE_INFINITE_APPLES = 1 << 0,
        GAME_MODE_WITH_ACCELERATION = 1 << 1,
        GAME_MODE_HIGH_SPEED = 1 << 2,
        GAME_MODE_50_APPLES = 1 << 3,
    };


    enum class GameStateType
    {
        SELECTING_MODE,
        PLAYING,
        GAME_OVER
    };


    struct LeaderboardEntry
    {
        std::string name;
        int score;
    };

    struct Game
    {
        Player player;
        Apple* apples = nullptr;
        int numApples = 0;
        Rock rocks[NUM_ROCKS];
        GameTexts texts;
        Background background;

        int score = 0;
        GameStateType gameState = GameStateType::SELECTING_MODE;


        unsigned int gameMode = GAME_MODE_WITH_ACCELERATION;


        sf::Text modeSelectionText;
        sf::Text gameOverMenuText;
        sf::Text leaderboardText;
        sf::Text congratulationText;


        std::vector<LeaderboardEntry> leaderboard;
        std::string playerName = "Player";


        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatenApplesBuffer;
        sf::SoundBuffer brokenApplesBuffer;
        sf::Sound sound;

        sf::Music music;
    };


    void InitGame(Game& game);
    void ResetGame(Game& game);
    void ReturnToMenu(Game& game);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinitializeGame(Game& game);


    void SetGameMode(Game& game, unsigned int mode);
    bool HasGameMode(Game& game, unsigned int mode);
    void ApplyGameMode(Game& game);
    void HandleModeSelection(Game& game);


    void HandlePlayerInput(Game& game);
    void HandleAppleCollisions(Game& game);
    void HandleRockCollisions(Game& game);
    void HandleBorderCollisions(Game& game);
    void HandleGameOverInput(Game& game);


    void InitModeSelectionText(Game& game);
    void InitGameOverMenuText(Game& game);
    void InitLeaderboardText(Game& game);
    void InitCongratulationText(Game& game);


    void GenerateLeaderboard(Game& game);
    void UpdateLeaderboard(Game& game);
    void SortLeaderboard(std::vector<LeaderboardEntry>& leaderboard);
    std::string FormatLeaderboard(const Game& game);
    void UpdateCongratulationText(Game& game);
}