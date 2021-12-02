#include "day_2/day_2.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <utility>

namespace aoc
{
	enum class Direction
	{
		FORWARD = 0,
		UP,
		DOWN,
		UNKNOWN
	};

	static std::vector<std::pair<Direction, int>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<std::pair<Direction, int>> directions;
		while (file)
		{
			std::string direction_str;
			int amount = 0;
			file >> direction_str >> amount;

			Direction direction = Direction::UNKNOWN;
			if (direction_str == "forward")
			{
				direction = Direction::FORWARD;
			}
			else if (direction_str == "down")
			{
				direction = Direction::DOWN;
			}
			else if (direction_str == "up")
			{
				direction = Direction::UP;
			}

			directions.push_back(std::make_pair(direction, amount));
		}

		return directions;
	}

	const std::string Day_2::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::pair<Direction, int>> directions = parse_input(input_path / "day_2.txt");

		int horizontal_pos = 0;
		int depth = 0;
		for (const auto& [direction, amount] : directions)
		{
			switch (direction)
			{
			case Direction::FORWARD:
				horizontal_pos += amount;
				break;
			case Direction::DOWN:
				depth += amount;
				break;
			case Direction::UP:
				depth -= amount;
				break;
			default:
				break;
			}
		}

		return fmt::format("Day 2 Part 1 | Final position: {}", horizontal_pos * depth);
	}

	const std::string Day_2::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::pair<Direction, int>> directions = parse_input(input_path / "day_2.txt");

		int horizontal_pos = 0;
		int depth = 0;
		int aim = 0;
		for (const auto& [direction, amount] : directions)
		{
			switch (direction)
			{
			case Direction::FORWARD:
				horizontal_pos += amount;
				depth += aim * amount;
				break;
			case Direction::DOWN:
				aim += amount;
				break;
			case Direction::UP:
				aim -= amount;
				break;
			default:
				break;
			}
		}

		return fmt::format("Day 2 Part 2 | Final position: {}", horizontal_pos * depth);
	}

} // aoc