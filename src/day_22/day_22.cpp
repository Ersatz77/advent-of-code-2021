#include "day_22/day_22.h"

#include "day_22/cube.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

namespace aoc
{
	static std::vector<Reboot_step> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<Reboot_step> steps;
		std::string state;
		int64_t min_x = 0;
		int64_t max_x = 0;
		int64_t min_y = 0;
		int64_t max_y = 0;
		int64_t min_z = 0;
		int64_t max_z = 0;
		for (std::string line; std::getline(file, line); )
		{
			std::istringstream line_stream(line);
			line_stream >> state;
			line_stream.ignore(3);
			line_stream >> min_x;
			line_stream.ignore(2);
			line_stream >> max_x;
			line_stream.ignore(3);
			line_stream >> min_y;
			line_stream.ignore(2);
			line_stream >> max_y;
			line_stream.ignore(3);
			line_stream >> min_z;
			line_stream.ignore(2);
			line_stream >> max_z;

			steps.emplace_back((state == "off" ? Cube_state::OFF : Cube_state::ON), min_x, max_x, min_y, max_y, min_z, max_z);
		}

		return steps;
	}

	const std::string Day_22::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<Reboot_step> steps = parse_input(input_path / "day_22.txt");

		std::vector<std::vector<std::vector<bool>>> grid(101, std::vector<std::vector<bool>>(101, std::vector<bool>(101, false)));
		for (const Reboot_step& step : steps)
		{
			if (step.min_x < -50 || step.max_x > 50 || step.min_y < -50 && step.max_y > 50 || step.min_z < -50 || step.max_z > 50)
			{
				continue;
			}

			for (int64_t z = step.min_z; z <= step.max_z; ++z)
			{
				for (int64_t y = step.min_y; y <= step.max_y; ++y)
				{
					for (int64_t x = step.min_x; x <= step.max_x; ++x)
					{
						grid[z + 50][y + 50][x + 50] = (step.state == Cube_state::ON ? true : false);
					}
				}
			}
		}

		size_t on_cubes = 0;
		for (const auto& y : grid)
		{
			for (const auto& x : y)
			{
				on_cubes += std::count(x.begin(), x.end(), true);
			}
		}

		return fmt::format("Day 22 Part 1 | On cubes: {}", on_cubes);
	}

	const std::string Day_22::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<Reboot_step> steps = parse_input(input_path / "day_22.txt");

		std::unordered_map<Cube, int> cubes;
		for (const Reboot_step& step : steps)
		{
			std::unordered_map<Cube, int> temp_cubes = cubes;
			Cube next_cube = step.to_cube();

			// If 'next_cube' intersects an existing cube, create a cube from the intersection 
			// and add it to the map with an inverted sign to cancel the other cubes out 
			for (const auto& [other_cube, sign] : cubes)
			{
				std::optional<Cube> intersection = next_cube.intersection(other_cube);
				if (intersection)
				{
					temp_cubes[*intersection] -= sign;
				}
			}

			if (step.state == Cube_state::ON)
			{
				++temp_cubes[next_cube];
			}

			cubes = std::move(temp_cubes);
		}

		size_t on_cubes = 0;
		for (const auto& [cube, sign] : cubes)
		{
			on_cubes += cube.volume() * sign;
		}

		return fmt::format("Day 22 Part 2 | On cubes: {}", on_cubes);
	}

} // aoc