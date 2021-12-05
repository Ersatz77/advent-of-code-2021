#include "day_5/day_5.h"

#include "day_5/point.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

namespace aoc
{
	int sign(int val)
	{
		if (val > 0)
		{
			return 1;
		}
		else if (val < 0)
		{
			return -1;
		}

		return 0;
	}

	std::vector<Point> get_points(const int x1, const int y1, const int x2, const int y2)
	{
		std::vector<Point> points;
		if (x1 == x2)
		{
			for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
			{
				points.emplace_back(x1, y);
			}
		}
		else if (y1 == y2)
		{
			for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
			{
				points.emplace_back(x, y2);
			}
		}
		else if (std::abs(x2 - x1) == std::abs(y2 - y1))
		{
			int length = std::abs(x1 - x2);
			int x = 0;
			int y = 0;
			for (int i = 0; i <= length; ++i)
			{
				x = x1 + (i * sign(x2 - x1));
				y = y1 + (i * sign(y2 - y1));
				points.emplace_back(x, y);
			}
		}

		return points;
	}

	std::unordered_map<Point, size_t> parse_input_part_1(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_map<Point, size_t> points;
		std::string line;
		std::string junk;
		char junk_ch = ' ';
		while (std::getline(file, line))
		{
			std::istringstream line_stream(line);
			int x1 = 0;
			int y1 = 0;
			int x2 = 0;
			int y2 = 0;
			line_stream >> x1 >> junk_ch >> y1 >> junk >> x2 >> junk_ch >> y2;

			if (x1 == x2 || y1 == y2)
			{
				for (auto& p : get_points(x1, y1, x2, y2))
				{
					points[p] += 1;
				}
			}
		}

		return points;
	}

	std::unordered_map<Point, size_t> parse_input_part_2(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_map<Point, size_t> points;
		std::string line;
		std::string junk;
		char junk_ch = ' ';
		while (std::getline(file, line))
		{
			std::istringstream line_stream(line);
			int x1 = 0;
			int y1 = 0;
			int x2 = 0;
			int y2 = 0;
			line_stream >> x1 >> junk_ch >> y1 >> junk >> x2 >> junk_ch >> y2;

			for (auto& p : get_points(x1, y1, x2, y2))
			{
				points[p] += 1;
			}
		}

		return points;
	}

	const std::string Day_5::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<Point, size_t> points = parse_input_part_1(input_path / "day_5.txt");
		size_t overlaps = 0;
		for (const auto& [key, value] : points)
		{
			if (value >= 2)
			{
				++overlaps;
			}
		}

		return fmt::format("Day 5 Part 1 | Overlaps: {}", overlaps);
	}

	const std::string Day_5::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<Point, size_t> points = parse_input_part_2(input_path / "day_5.txt");
		size_t overlaps = 0;
		for (const auto& [key, value] : points)
		{
			if (value >= 2)
			{
				++overlaps;
			}
		}

		return fmt::format("Day 5 Part 2 | Overlaps: {}", overlaps);
	}

} // aoc