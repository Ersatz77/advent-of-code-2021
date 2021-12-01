#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace aoc
{
	static std::vector<int> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::vector<int> numbers;
		while (file)
		{
			int number = 0;
			file >> number;
			numbers.push_back(number);
		}

		return numbers;
	}

	const std::string Day_1::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int> depth_readings = parse_input(input_path / "day_1.txt");

		int depth_increases = 0;
		for (size_t i = 1; i < depth_readings.size(); ++i)
		{
			if (depth_readings[i] > depth_readings[i - 1])
			{
				++depth_increases;
			}
		}

		return fmt::format("Day 1 Part 1 | Depth increases: {}", depth_increases);
	}

	const std::string Day_1::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int> depth_readings = parse_input(input_path / "day_1.txt");

		int depth_increases = 0;
		for (size_t i = 3; i < depth_readings.size(); ++i)
		{
			int prev_depth_sum = depth_readings[i - 1] + depth_readings[i - 2] + depth_readings[i - 3];
			int current_depth_sum = depth_readings[i] + depth_readings[i - 1] + depth_readings[i - 2];
			if (current_depth_sum > prev_depth_sum)
			{
				++depth_increases;
			}
		}

		return fmt::format("Day 1 Part 2 | Depth increases: {}", depth_increases);
	}

} // aoc