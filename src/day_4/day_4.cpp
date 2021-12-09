#include "day_4/day_4.h"

#include "day_4/bingo_board.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <string>

namespace aoc
{
	static void parse_input(const std::filesystem::path& path, std::vector<int>& numbers, std::vector<Bingo_board>& boards)
	{
		std::ifstream file = open_file(path);
		std::string line;

		// Get first line with numbers
		std::getline(file, line);
		std::istringstream numbers_stream(line);
		for (int number = 0; numbers_stream >> number; )
		{
			numbers.push_back(number);
			numbers_stream.ignore(1);
		}

		// Get bingo boards
		while (file)
		{
			Bingo_board board;
			file >> board;
			boards.push_back(board);
			file.ignore(1);
		}
	}

	const std::string Day_4::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int> numbers;
		std::vector<Bingo_board> boards;
		parse_input(input_path / "day_4.txt", numbers, boards);

		int winning_board_score = 0;
		bool found_winner = false;
		for (size_t i = 0; i < numbers.size() && !found_winner; ++i)
		{
			for (Bingo_board& board : boards)
			{
				if (board.mark_square(numbers[i]))
				{
					winning_board_score = numbers[i] * board.sum_of_unmarked();
					found_winner = true;
					break;
				}
			}
		}

		return fmt::format("Day 4 Part 1 | Winning board score: {}", winning_board_score);
	}

	const std::string Day_4::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int> numbers;
		std::vector<Bingo_board> boards;
		parse_input(input_path / "day_4.txt", numbers, boards);

		int last_winning_board_score = 0;
		for (size_t i = 0; i < numbers.size(); ++i)
		{
			std::vector<Bingo_board> temp_boards;
			for (Bingo_board& board : boards)
			{
				if (board.mark_square(numbers[i]))
				{
					last_winning_board_score = numbers[i] * board.sum_of_unmarked();
				}
				else
				{
					temp_boards.push_back(std::move(board));
				}
			}

			boards = std::move(temp_boards);
		}

		return fmt::format("Day 4 Part 2 | Last winning board score: {}", last_winning_board_score);
	}

} // aoc