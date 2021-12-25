#include "day_25/day_25.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <string>
#include <unordered_set>
#include <utility>

namespace aoc
{
	static std::pair<std::unordered_set<Point>, std::unordered_set<Point>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_set<Point> east;
		std::unordered_set<Point> south;

		int y = 0;
		for (std::string line; std::getline(file, line); )
		{
			int x = 0;
			std::istringstream line_stream(line);
			for (char c = ' '; line_stream >> c; )
			{
				switch (c)
				{
				case '>':
					east.emplace(x, y);
					break;
				case 'v':
					south.emplace(x, y);
					break;
				default:
					break;
				}

				++x;
			}

			++y;
		}

		return std::make_pair(east, south);
	}

	static std::pair<int, int> max_bounds(const std::unordered_set<Point>& east, const std::unordered_set<Point>& south)
	{
		int max_x = std::numeric_limits<int>::min();
		int max_y = std::numeric_limits<int>::min();
		for (const auto& e : east)
		{
			max_x = std::max(max_x, e.x);
			max_y = std::max(max_y, e.y);
		}

		for (const auto& s : south)
		{
			max_x = std::max(max_x, s.x);
			max_y = std::max(max_y, s.y);
		}

		return std::make_pair(max_x, max_y);
	}

	const std::string Day_25::part_1(const std::filesystem::path& input_path) const
	{
		auto [east, south] = parse_input(input_path / "day_25.txt");
		const auto [max_x, max_y] = max_bounds(east, south);

		size_t step = 1;
		while (true)
		{
			bool modified = false;
			std::unordered_set<Point> next_east;
			std::unordered_set<Point> next_south;

			// Move east
			for (const auto& e : east)
			{
				Point next_pos{ (e.x + 1) % (max_x + 1) , e.y};
				if (!east.contains(next_pos) && !south.contains(next_pos))
				{
					next_east.insert(next_pos);
					modified = true;
				}
				else
				{
					next_east.insert(e);
				}
			}

			// Move south
			// Checks the next east values to prevent overlaps when moving down
			for (const auto& s : south)
			{
				Point next_pos{ s.x, (s.y + 1) % (max_y + 1)};
				if (!next_east.contains(next_pos) && !south.contains(next_pos))
				{
					next_south.insert(next_pos);
					modified = true;
				}
				else
				{
					next_south.insert(s);
				}
			}

			if (!modified)
			{
				break;
			}

			east = std::move(next_east);
			south = std::move(next_south);
			++step;
		}

		return fmt::format("Day 25 Part 1 | Stopped moving in {} steps", step);
	}

	const std::string Day_25::part_2(const std::filesystem::path& input_path) const
	{
		auto [east, south] = parse_input(input_path / "day_25.txt");
		return fmt::format("Day 25 Part 2 | You remotely started the sleigh!");
	}

} // aoc