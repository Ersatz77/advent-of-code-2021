#include "day_24/day_24.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace aoc
{
	const std::string Day_24::part_1(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 24 Part 1 | {}", input_path.filename().string());
	}

	const std::string Day_24::part_2(const std::filesystem::path& input_path) const
	{
		return fmt::format("Day 24 Part 2 | {}", input_path.filename().string());
	}

} // aoc