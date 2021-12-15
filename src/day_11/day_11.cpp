#include "day_11/day_11.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>
#include <queue>

namespace aoc
{
	static std::array<std::array<int, 10>, 10> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::array<std::array<int, 10>, 10> grid = {};
		char temp = ' ';
		for (size_t y = 0; y < grid.size(); ++y)
		{
			for (size_t x = 0; x < grid.front().size(); ++x)
			{
				file >> temp;
				grid[y][x] = static_cast<int>(temp) - 48;
			}
		}

		return grid;
	}

	static int step(std::array<std::array<int, 10>, 10>& grid)
	{
		size_t height = grid.size();
		size_t width = grid.front().size();

		// Increment all points and add them to the queue if they're going to flash
		std::queue<Point> flashes;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (++grid[y][x] == 10)
				{
					flashes.push(Point{ x, y });
				}
			}
		}

		// Flash points in queue
		// More points may be added as the flashing chains
		int num_flashes = 0;
		while (!flashes.empty())
		{
			Point p = flashes.front();
			flashes.pop();
			++num_flashes;

			for (const auto& adj : p.adjacent())
			{
				if (adj.x >= 0 && adj.y >= 0 && adj.x < width && adj.y < height)
				{
					if (++grid[adj.y][adj.x] == 10)
					{
						flashes.push(Point{ adj.x, adj.y });
					}
				}
			}
		}

		// Reset points that are greater than 9 since we use those values to determine
		// if a point has already been flashed
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (grid[y][x] >= 10)
				{
					grid[y][x] = 0;
				}
			}
		}

		return num_flashes;
	}

	const std::string Day_11::part_1(const std::filesystem::path& input_path) const
	{
		std::array<std::array<int, 10>, 10> grid = parse_input(input_path / "day_11.txt");

		int flashes = 0;
		for (size_t i = 0; i < 100; ++i)
		{
			flashes += step(grid);
		}

		return fmt::format("Day 11 Part 1 | Flashes after 100 steps: {}", flashes);
	}

	const std::string Day_11::part_2(const std::filesystem::path& input_path) const
	{
		std::array<std::array<int, 10>, 10> grid = parse_input(input_path / "day_11.txt");

		size_t iteration = 1;
		while (true)
		{
			if (step(grid) == 100)
			{
				break;
			}

			++iteration;
		}

		return fmt::format("Day 11 Part 2 | First iteration with a synced flash: {}", iteration);
	}

} // aoc