#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <string>

namespace aoc
{
	const std::string Day_1::part_1(const std::filesystem::path& path) const
	{
		return fmt::format("Day 1 Part 1 | {}", "Foo");
	}

	const std::string Day_1::part_2(const std::filesystem::path& path) const
	{
		return fmt::format("Day 1 Part 1 | {}", "Bar");
	}

} // aoc