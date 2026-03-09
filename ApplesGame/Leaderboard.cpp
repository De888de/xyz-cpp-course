#include "Leaderboard.h"
#include "Utils.h"
#include <sstream>

namespace ApplesGame
{
    void Leaderboard::Generate()
    {
        entries.clear();

        // Fictional players
        std::vector<std::string> names = { "Alice", "Bob", "Carol", "Dave", "Eve", "Frank", "Grace", "Henry", "Ivy", "Jack" };
        std::vector<int> scores = { 120, 85, 55, 30, 150, 95, 70, 45, 110, 65 };

        for (size_t i = 0; i < names.size(); ++i)
        {
            LeaderboardEntry entry;
            entry.name = names[i];
            entry.score = scores[i];
            entries.push_back(entry);
        }

        LeaderboardEntry playerEntry;
        playerEntry.name = playerName;
        playerEntry.score = 0;
        entries.push_back(playerEntry);

        Sort();
    }

    void Leaderboard::UpdatePlayerScore(int score)
    {
        for (auto& entry : entries)
        {
            if (entry.name == playerName)
            {
                entry.score = score;
                break;
            }
        }

        Sort();
    }

    void Leaderboard::Sort()
    {
        
        ApplesGame::Sort(entries, CompareLeaderboardByScoreDesc);
    }

    std::string Leaderboard::Format() const
    {
        std::stringstream ss;
        ss << "===== LEADERBOARD =====\n\n";

        int count = 0;
        for (const auto& entry : entries)
        {
            if (count >= 5) break; // We only show the top 5

            ss << count + 1 << ". " << entry.name;

            // Adding alignment points
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
}