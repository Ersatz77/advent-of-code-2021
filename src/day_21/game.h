#ifndef AOC_2021_DAY_21_GAME_H
#define AOC_2021_DAY_21_GAME_H

#include <functional>
#include <cstdint>

namespace aoc
{
	struct Player
	{
		int pos = 0;
		int score = 0;
	};

	struct Gamestate
	{
		Player player_1;
		Player player_2;
		uint8_t turn;
	};

} // aoc

namespace std
{
	template <>
	struct hash<aoc::Player>
	{
		std::size_t operator()(const aoc::Player& p) const
		{
			return ((hash<int>()(p.pos)) ^ (hash<int>()(p.score) << 1));
		}
	};

	template <>
	struct hash<aoc::Gamestate>
	{
		std::size_t operator()(const aoc::Gamestate& g) const
		{
			return ((hash<aoc::Player>()(g.player_1) ^ (hash<aoc::Player>()(g.player_2) << 1)) >> 1) ^ (hash<uint8_t>()(g.turn) << 1);;
		}
	};

} // std

#endif // !AOC_2021_DAY_21_GAME_H
