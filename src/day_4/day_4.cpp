#include "day_4/day_4.h"

#include "day_4/bingo_board.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <string>

namespace aoc
{
	std::vector<int> parse_numbers(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::string line;

		// Get first line
		std::getline(file, line);

		// Convert line to a vector of ints
		std::vector<int> numbers;
		numbers.reserve(100);
		std::istringstream numbers_stream(line);
		for (int number = 0; numbers_stream >> number; )
		{
			numbers.push_back(number);
			numbers_stream.ignore(1);
		}

		return numbers;
	}

	std::vector<Square> parse_bingo_row(const std::string& line)
	{
		std::vector<Square> row;
		std::istringstream row_stream(line);
		for (int number = 0; row_stream >> number; )
		{
			row.push_back(Square{ number, false });
		}

		return row;
	}

	std::vector<Bingo_board> parse_bingo_cards(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::string line;

		// Skip line with numbers
		std::getline(file, line);

		// Get bingo boards
		std::vector<Bingo_board> boards;
		boards.reserve(100);
		while (file)
		{
			// Add rows to board
			Bingo_board board;
			while (std::getline(file, line) && !line.empty())
			{
				board.add_row(parse_bingo_row(line));
			}

			// Add board to vector
			boards.push_back(board);
		}
		
		return boards;
	}

	const std::string Day_4::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int> numbers = parse_numbers(input_path / "day_4.txt");
		std::vector<Bingo_board> boards = parse_bingo_cards(input_path / "day_4.txt");

		int winning_board_score = 0;
		bool found_winner = false;
		for (size_t i = 0; i < numbers.size() && !found_winner; ++i)
		{
			for (Bingo_board& board : boards)
			{
				board.mark_square(numbers[i]);
				if (board.winner())
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
		std::vector<int> numbers = parse_numbers(input_path / "day_4.txt");
		std::vector<Bingo_board> boards = parse_bingo_cards(input_path / "day_4.txt");

		int last_winning_board_score = 0;
		for (size_t i = 0; i < numbers.size(); ++i)
		{
			std::vector<Bingo_board> temp_boards;
			for (Bingo_board& board : boards)
			{
				board.mark_square(numbers[i]);
				if (board.winner())
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