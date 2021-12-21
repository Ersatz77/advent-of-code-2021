#include "day_21/day_21.h"

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
#include <utility>

namespace aoc
{
	struct Player
	{
		int pos = 0;
		int score = 0;
	};

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

	static void play_quantum(const Player& player_1, const Player& player_2, const int8_t turn, const int64_t occurrences, int64_t& player_1_wins, int64_t& player_2_wins)
	{
		if (player_1.score >= 21)
		{
			player_1_wins += occurrences;
			return;
		}

		if (player_2.score >= 21)
		{
			player_2_wins += occurrences;
			return;
		}
		
		constexpr std::array<std::array<int, 2>, 7> dirac_rolls = { {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3},{9, 1}} };
		for (size_t i = 0; i < dirac_rolls.size(); ++i)
		{
			int roll = dirac_rolls[i].front();
			int count = dirac_rolls[i].back();

			Player new_player_1 = player_1;
			Player new_player_2 = player_2;
			Player& current = (turn == 0) ? new_player_1 : new_player_2;
			current.pos = ((current.pos + roll - 1) % 10) + 1;
			current.score += current.pos;

			play_quantum(new_player_1, new_player_2, ~turn, occurrences * count, player_1_wins, player_2_wins);
		}
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

		int64_t player_1_wins = 0;
		int64_t player_2_wins = 0;
		play_quantum(players.first, players.second, 0, 1, player_1_wins, player_2_wins);

		return fmt::format("Day 21 Part 2 | Most wins: {}", std::max(player_1_wins, player_2_wins));
	}

} // aoc