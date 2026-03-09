#include "Utils.h"

namespace ApplesGame
{
    bool CompareLeaderboardByScoreDesc(const LeaderboardEntry& a, const LeaderboardEntry& b)
    {
        return a.score < b.score; // to sort in descending order
    }
}