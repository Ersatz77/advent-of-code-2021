#include "day_17/day_17.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <utility>

namespace aoc
{
	struct Target_area
	{
		int min_x = 0;
		int max_x = 0;
		int min_y = 0;
		int max_y = 0;
	};

	static Target_area parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		Target_area target;
		file.ignore(15);
		file >> target.min_x;
		file.ignore(2);
		file >> target.max_x;
		file.ignore(4);
		file >> target.max_y;
		file.ignore(2);
		file >> target.min_y;

		return target;
	}

	static bool in_target_area(const Point& p, const Target_area& target)
	{
		return p.x >= target.min_x && p.x <= target.max_x && p.y <= target.min_y && p.y >= target.max_y;
	}

	static bool out_of_range(const Point& p, const Target_area& target)
	{
		return p.x > target.max_x || p.y < target.max_y;
	}

	static std::pair<bool, int> launch_probe(int vel_x, int vel_y, const Target_area& target)
	{
		Point p = Point::origin;
		int highest_y = 0;
		while (!in_target_area(p, target))
		{
			p.x += (vel_x > 0) ? vel_x-- : 0;
			p.y += vel_y--;
			highest_y = std::max(highest_y, p.y);
			if (out_of_range(p, target))
			{
				return std::make_pair(false, 0);
			}
		}

		return std::make_pair(true, highest_y);
	}

	const std::string Day_17::part_1(const std::filesystem::path& input_path) const
	{
		Target_area target = parse_input(input_path / "day_17.txt");

		int highest_y = 0;
		for (int y = 0; y <= -target.max_y; ++y)
		{
			for (int x = 0; x <= target.max_x; ++x)
			{
				std::pair<bool, int> output = launch_probe(x, y, target);
				if (output.first)
				{
					highest_y = std::max(highest_y, output.second);
				}
			}
		}

		return fmt::format("Day 17 Part 1 | Highest Y value: {}", highest_y);
	}

	const std::string Day_17::part_2(const std::filesystem::path& input_path) const
	{
		Target_area target = parse_input(input_path / "day_17.txt");

		std::unordered_set<Point> unique_velocities;
		for (int y = target.max_y; y <= -target.max_y; ++y)
		{
			for (int x = 0; x <= target.max_x; ++x)
			{
				std::pair<bool, int> output = launch_probe(x, y, target);
				if (output.first)
				{
					unique_velocities.insert(Point{ x, y });
				}
			}
		}

		return fmt::format("Day 17 Part 2 | Unique initial velocities: {}", unique_velocities.size());
	}

} // aoc