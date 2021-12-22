#include "day_21/day_21.h"

#include "day_21/game.h"
#include "day_21/dice.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <string>
#include <array>
#include <unordered_map>
#include <utility>

namespace aoc
{
	static std::pair<Player, Player> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::string player_1_line;
		std::string player_2_line;
		std::getline(file, player_1_line);
		std::getline(file, player_2_line);

		int player_1_starting_pos = static_cast<int>(player_1_line.back()) - 48;
		int player_2_starting_pos = static_cast<int>(player_2_line.back()) - 48;

		return std::make_pair(Player{ player_1_starting_pos, 0}, Player{player_2_starting_pos, 0});
	}

	static std::pair<int64_t, int64_t> play_quantum(const Player& player_1, const Player& player_2, const uint8_t turn, 
		std::unordered_map<Gamestate, std::pair<int64_t, int64_t>>& cache)
	{
		const auto it = cache.find(Gamestate{player_1, player_2, turn});
		if (it != cache.end())
		{
			return it->second;
		}

		std::pair<int64_t, int64_t> wins = { 0, 0 };
		uint8_t player_for_next_turn = (turn == 0 ? 1 : 0);

		constexpr std::array<int, 27> dirac_rolls = { 3, 4, 5, 4, 5, 6, 5, 6, 7, 4, 5, 6, 5, 6, 7, 6, 7, 8, 5, 6, 7, 6, 7, 8, 7, 8, 9 };
		for (const int roll : dirac_rolls)
		{
			Player new_player_1 = player_1;
			Player new_player_2 = player_2;
			Player& current = (turn == 0) ? new_player_1 : new_player_2;
			int64_t& current_wins = (turn == 0) ? wins.first : wins.second;
			current.pos = ((current.pos + roll - 1) % 10) + 1;
			current.score += current.pos;

			if (current.score >= 21)
			{
				++current_wins;
			}
			else
			{
				const auto [player_1_wins, player_2_wins] = play_quantum(new_player_1, new_player_2, player_for_next_turn, cache);
				wins.first += player_1_wins;
				wins.second += player_2_wins;
			}
		}

		cache[Gamestate{ player_1, player_2, turn }] = wins;
		cache[Gamestate{ player_2, player_1, player_for_next_turn }] = std::make_pair(wins.second, wins.first);
		return wins;
	}

	const std::string Day_21::part_1(const std::filesystem::path& input_path) const
	{
		std::pair<Player, Player> players = parse_input(input_path / "day_21.txt");
		
		Dice dice;
		uint8_t turn = 0;
		while (players.first.score < 1000 || players.second.score < 1000)
		{
			Player& current = (turn == 0) ? players.first : players.second;
			int roll = dice.roll_three();
			current.pos = ((current.pos + roll - 1) % 10) + 1;
			current.score += current.pos;

			if (current.score >= 1000)
			{
				break;
			}

			turn = ~turn;
		}

		int score = ((players.first.score >= 1000) ? players.second.score : players.first.score) * dice.total_rolls();

		return fmt::format("Day 21 Part 1 | Score: {}", score);
	}

	const std::string Day_21::part_2(const std::filesystem::path& input_path) const
	{
		std::pair<Player, Player> players = parse_input(input_path / "day_21.txt");

		std::unordered_map<Gamestate, std::pair<int64_t, int64_t>> cache;
		const auto [player_1_wins, player_2_wins] = play_quantum(players.first, players.second, 0, cache);

		return fmt::format("Day 21 Part 2 | Most wins: {}", std::max(player_1_wins, player_2_wins));
	}

} // aoc