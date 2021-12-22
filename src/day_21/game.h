#ifndef AOC_2020_DAY_21_GAME_H
#define AOC_2020_DAY_21_GAME_H

#include "utility/utility.h"

#include <functional>
#include <cstdint>

namespace aoc
{
	struct Player
	{
		int pos = 0;
		int score = 0;
	};

	bool operator==(const Player& lhs, const Player& rhs);

	struct Gamestate
	{
		Player player_1;
		Player player_2;
		uint8_t turn;
	};

	bool operator==(const Gamestate& lhs, const Gamestate& rhs);

} // aoc

namespace std
{
	template <>
	struct hash<aoc::Player>
	{
		std::size_t operator()(const aoc::Player& p) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, p.pos);
			aoc::hash_combine(seed, p.score);
			return seed;
		}
	};

	template <>
	struct hash<aoc::Gamestate>
	{
		std::size_t operator()(const aoc::Gamestate& g) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, g.player_1);
			aoc::hash_combine(seed, g.player_2);
			aoc::hash_combine(seed, g.turn);
			return seed;
		}
	};

} // std

#endif // !AOC_2020_DAY_21_GAME_H
