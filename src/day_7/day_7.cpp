#include "day_7/day_7.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

namespace aoc
{
	static std::vector<int> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<int> crabs;
		for (int number = 0; file >> number; )
		{
			crabs.push_back(number);
			file.ignore(1);
		}

		return crabs;
	}

	const std::string Day_7::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int> crabs = parse_input(input_path / "day_7.txt");

		const auto min_it = std::min_element(crabs.begin(), crabs.end());
		const auto max_it = std::max_element(crabs.begin(), crabs.end());

		int max = (max_it != crabs.end()) ? *max_it : 0;
		int min = (min_it != crabs.end()) ? *min_it : 0;

		int min_fuel = std::numeric_limits<int>::max();
		for (int i = min; i <= max; ++i)
		{
			int sum = 0;
			for (const int c : crabs)
			{
				sum += std::abs(c - i);
			}

			min_fuel = std::min(min_fuel, sum);
		}

		return fmt::format("Day 7 Part 1 | Minimum fuel: {}", min_fuel);
	}

	const std::string Day_7::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int> crabs = parse_input(input_path / "day_7.txt");

		const auto min_it = std::min_element(crabs.begin(), crabs.end());
		const auto max_it = std::max_element(crabs.begin(), crabs.end());

		int max = (max_it != crabs.end()) ? *max_it : 0;
		int min = (min_it != crabs.end()) ? *min_it : 0;

		int min_fuel = std::numeric_limits<int>::max();
		for (int i = min; i <= max; ++i)
		{
			int sum = 0;
			for (const int c : crabs)
			{
				sum += (std::abs(c - i) * (std::abs(c - i) + 1)) / 2;
			}

			min_fuel = std::min(min_fuel, sum);
		}

		return fmt::format("Day 7 Part 2 | Minimum fuel: {}", min_fuel);
	}

} // aoc