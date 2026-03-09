#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    // СStructure for entry in the leaderboard
    struct LeaderboardEntry
    {
        std::string name;
        int score = 0; 
    };

    // A class for managing the leaderboard
    class Leaderboard
    {
    private:
        std::vector<LeaderboardEntry> entries;
        std::string playerName = "Player";

    public:
        void Generate();  // Generates a table with fictional players
        void UpdatePlayerScore(int score);  // Updates the current player's score
        void Sort();  // Sorts the table in descending order
        std::string Format() const;  // Formats the table for display
        const std::vector<LeaderboardEntry>& GetEntries() const { return entries; }
        void Clear() { entries.clear(); }
    };
}