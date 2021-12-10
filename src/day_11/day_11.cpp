#include "day_11/day_11.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace aoc
{
	const std::string Day_11::part_1(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 11 Part 1 | {}", input_path.filename().string());
	}

	const std::string Day_11::part_2(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 11 Part 1 | {}", input_path.filename().string());
	}

} // aoc