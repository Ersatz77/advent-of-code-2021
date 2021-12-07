#include "day_5/day_5.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>
#include <vector>

namespace aoc
{
	constexpr size_t grid_width = 1000;
	constexpr size_t grid_height = 1000;

	static int sign(int val)
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

	static std::vector<Point> get_points(const int x1, const int y1, const int x2, const int y2)
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

	static int* parse_input_part_1(const std::filesystem::path& path, const size_t width, const size_t height)
	{
		std::ifstream file = open_file(path);

		int* grid = new int[width * height]();
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
					++grid[(p.y * width) + p.x];
				}
			}
		}

		return grid;
	}

	static int* parse_input_part_2(const std::filesystem::path& path, const size_t width, const size_t height)
	{
		std::ifstream file = open_file(path);

		int* grid = new int[width * height]();
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
				++grid[(p.y * width) + p.x];
			}
		}

		return grid;
	}

	static size_t num_overlaps(int const * const grid, const size_t width, const size_t height)
	{
		size_t overlaps = 0;
		for (size_t i = 0; i < width * height; ++i)
		{
			if (grid[i] >= 2)
			{
				++overlaps;
			}
		}

		return overlaps;
	}

	const std::string Day_5::part_1(const std::filesystem::path& input_path) const
	{
		int* grid = parse_input_part_1(input_path / "day_5.txt", grid_width, grid_height);
		size_t overlaps = num_overlaps(grid, grid_width, grid_height);

		delete[] grid;
		return fmt::format("Day 5 Part 1 | Overlaps: {}", overlaps);
	}

	const std::string Day_5::part_2(const std::filesystem::path& input_path) const
	{
		int* grid = parse_input_part_2(input_path / "day_5.txt", grid_width, grid_height);
		size_t overlaps = num_overlaps(grid, grid_width, grid_height);

		delete[] grid;
		return fmt::format("Day 5 Part 2 | Overlaps: {}", overlaps);
	}

} // aoc