#include "day_21/game.h"

namespace aoc
{
	bool operator==(const Player& lhs, const Player& rhs)
	{
		return lhs.pos == rhs.pos && lhs.score == rhs.score;
	}

	bool operator==(const Gamestate& lhs, const Gamestate& rhs)
	{
		return lhs.player_1 == rhs.player_1 && lhs.player_2 == rhs.player_2 && lhs.turn == rhs.turn;
	}

} // aoc