#include "day_2/day_2.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace aoc
{
	const std::string Day_2::part_1(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 2 Part 1 | {}", input_path.string());
	}

	const std::string Day_2::part_2(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 2 Part 2 | {}", input_path.string());
	}

} // aoc