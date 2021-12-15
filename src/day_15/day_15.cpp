#include "day_15/day_15.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>

namespace aoc
{
	static std::vector<std::vector<int>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<std::vector<int>> grid;
		for (std::string line; file >> line; )
		{
			std::vector<int> column;
			for (const char c : line)
			{
				column.push_back(static_cast<int>(c) - 48);
			}

			grid.push_back(column);
		}

		return grid;
	}

	static std::vector<std::vector<int>> scale(const std::vector<std::vector<int>>& grid)
	{
		size_t old_width = grid.front().size();
		size_t old_height = grid.size();

		size_t width = grid.front().size() * 5;
		size_t height = grid.size() * 5;

		std::vector<std::vector<int>> new_grid(height, std::vector<int>(width, 0));
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				size_t quad_x = x / old_width;
				size_t quad_y = y / old_height;

				int risk = grid[y % old_height][x % old_width];
				risk += static_cast<int>(quad_x + quad_y);
				risk = (risk > 9) ? risk % 9 : risk;

				new_grid[y][x] = risk;
			}
		}

		return new_grid;
	}

	static int lowest_cost(const std::vector<std::vector<int>>& grid)
	{
		size_t width = grid.front().size();
		size_t height = grid.size();

		// Find shortest path using Dijkstra
		std::unordered_map<Point, int> costs;
		std::unordered_set<Point> visited;
		std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, std::greater<std::pair<int, Point>>> to_visit;
		to_visit.push(std::make_pair(0, Point::origin));
		while (!to_visit.empty())
		{
			int cost = to_visit.top().first;
			Point point = to_visit.top().second;
			to_visit.pop();

			if (visited.contains(point))
				continue;

			visited.insert(point);
			costs[point] = cost;

			for (const auto& adj : point.adjacent_cardinal())
			{
				if (adj.x >= 0 && adj.x < width && adj.y >= 0 && adj.y < height)
				{
					int adjacent_cost = cost + grid[adj.y][adj.x];
					to_visit.push(std::make_pair(adjacent_cost, Point{ adj.x, adj.y }));
				}
			}
		}

		const auto bottom_left_it = costs.find(Point{ static_cast<int>(width) - 1, static_cast<int>(height) - 1 });
		return (bottom_left_it != costs.end()) ? bottom_left_it->second : 0;
	}

	const std::string Day_15::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<int>> grid = parse_input(input_path / "day_15.txt");
		return fmt::format("Day 15 Part 1 | Lowest path cost: {}", lowest_cost(grid));
	}

	const std::string Day_15::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<int>> grid = parse_input(input_path / "day_15.txt");
		grid = scale(grid);
		return fmt::format("Day 15 Part 2 | Lowest path cost: {}", lowest_cost(grid));
	}

} // aoc