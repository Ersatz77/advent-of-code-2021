#include "day_6/day_6.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <string>
#include <array>

namespace aoc
{
	std::array<size_t, 9> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::array<size_t, 9> fish = {};
		for (int initial_days = 0; file >> initial_days; )
		{
			++fish[initial_days];
			file.ignore(1);
		}

		return fish;
	}

	std::array<size_t, 9> cycle_fish(std::array<size_t, 9> fish, const size_t cycles)
	{
		for (size_t i = 0; i < cycles; ++i)
		{
			std::array<size_t, 9> temp_fish = {};
			for (size_t day = 0; day < 9; ++day)
			{
				size_t num_fish = fish[day];
				if (day == 0)
				{
					temp_fish[6] += num_fish;
					temp_fish[8] += num_fish;
					continue;
				}

				temp_fish[day - 1] += num_fish;
			}

			fish = std::move(temp_fish);
		}

		return fish;
	}

	const std::string Day_6::part_1(const std::filesystem::path& input_path) const
	{
		std::array<size_t, 9> fish = parse_input(input_path / "day_6.txt");
		fish = cycle_fish(fish, 80);
		size_t sum = std::accumulate(fish.begin(), fish.end(), 0ull);
		return fmt::format("Day 6 Part 1 | Fish after 80 days: {}", sum);
	}

	const std::string Day_6::part_2(const std::filesystem::path& input_path) const
	{
		std::array<size_t, 9> fish = parse_input(input_path / "day_6.txt");
		fish = cycle_fish(fish, 256);
		size_t sum = std::accumulate(fish.begin(), fish.end(), 0ULL);
		return fmt::format("Day 6 Part 2 | Fish after 256 days: {}", sum);
	}

} // aoc