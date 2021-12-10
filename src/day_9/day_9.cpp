#include "day_9/day_9.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace aoc
{
	static std::vector<std::vector<int8_t>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		
		std::vector<std::vector<int8_t>> height_map;
		for (std::string line; std::getline(file, line); )
		{
			std::vector<int8_t> row;
			std::istringstream line_stream(line);
			for (char c = ' '; line_stream >> c; )
			{
				row.push_back(static_cast<int8_t>(c) - 48);
			}

			height_map.push_back(row);
		}

		return height_map;
	}

	static int8_t value_at_pos(const int x, const int y, const std::vector<std::vector<int8_t>>& height_map)
	{
		size_t width = height_map.front().size();
		size_t height = height_map.size();
		if (x < 0 || y < 0 || y >= height || x >= width)
		{
			return -1;
		}

		return height_map[y][x];
	}

	static bool is_low_point(const int x, const int y, const std::vector<std::vector<int8_t>>& height_map)
	{
		int8_t center = value_at_pos(x, y, height_map);
		if (center == -1)
		{
			return false;
		}

		constexpr std::array<int, 8> offsets = { 0, 1, 0, -1, 1, 0, -1, 0 };
		for (size_t i = 1; i < offsets.size(); i += 2)
		{
			int8_t adjacent = value_at_pos(x + offsets[i - 1], y + offsets[i], height_map);
			if (center >= adjacent)
			{
				return false;
			}
		}

		return true;
	}

	static int64_t flood(const int x, const int y, std::vector<std::vector<int8_t>>& height_map)
	{
		int64_t size = 1;
		height_map[y][x] = -1;

		constexpr std::array<int, 8> offsets = { 0, 1, 0, -1, 1, 0, -1, 0 };
		for (size_t i = 1; i < offsets.size(); i += 2)
		{
			int8_t value = value_at_pos(x + offsets[i - 1], y + offsets[i], height_map);
			if (value == -1 || value == 9)
			{
				continue;
			}

			size += flood(x + offsets[i - 1], y + offsets[i], height_map);
		}

		return size;
	}

	const std::string Day_9::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<int8_t>> height_map = parse_input(input_path / "day_9.txt");
		size_t width = height_map.front().size();
		size_t height = height_map.size();

		int64_t sum = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (is_low_point(x, y, height_map))
				{
					sum += value_at_pos(x, y, height_map) + 1LL;
				}
			}
		}

		return fmt::format("Day 9 Part 1 | Risk level sum: {}", sum);
	}

	const std::string Day_9::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<int8_t>> height_map = parse_input(input_path / "day_9.txt");
		size_t width = height_map.front().size();
		size_t height = height_map.size();

		// Get low points
		std::vector<int> low_points;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (is_low_point(x, y, height_map))
				{
					low_points.push_back(x);
					low_points.push_back(y);
				}
			}
		}

		// Get the size of every basin
		std::vector<uint64_t> basins;
		for (size_t i = 1; i < low_points.size(); i += 2)
		{
			int x = low_points[i - 1];
			int y = low_points[i];
			basins.push_back(flood(x, y, height_map));
		}


		// Get the product of the largest 3 basins
		std::sort(basins.begin(), basins.end());
		int64_t largest = 1;
		for (auto it = basins.end() - 3; it != basins.end(); ++it)
		{
			largest *= *it;
		}

		return fmt::format("Day 9 Part 2 | Largest basins: {}", largest);
	}

} // aoc