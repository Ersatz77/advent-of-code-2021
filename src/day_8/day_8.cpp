#include "day_8/day_8.h"

#include "day_8/signal.h"
#include "day_8/digit.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <string>
#include <vector>

namespace aoc
{
	static std::vector<Signal> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<Signal> entries;
		for (std::string line; std::getline(file, line); )
		{
			std::istringstream line_stream(line);
			Signal signal;
			line_stream >> signal;
			entries.push_back(signal);
		}

		return entries;
	}

	const std::string Day_8::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<Signal> entries = parse_input(input_path / "day_8.txt");

		uint64_t unique_outputs = 0;
		for (const auto& entry : entries)
		{
			unique_outputs += entry.unique_outputs();
		}

		return fmt::format("Day 8 Part 1 | Unique outputs: {}", unique_outputs);
	}

	const std::string Day_8::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<Signal> entries = parse_input(input_path / "day_8.txt");

		int64_t sum = 0;
		for (const auto& entry : entries)
		{
			sum += entry.decode_output();
		}

		return fmt::format("Day 8 Part 2 | Output sum: {}", sum);
	}

} // aoc