#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
	const std::string Day_1::part_1(const std::filesystem::path& path) const
	{
		std::ifstream file = open_file(path / "test.txt");
		std::vector<std::string> lines;
		for (std::string temp; file >> temp; )
		{
			lines.push_back(temp);
		}

		return fmt::format("Day 1 Part 1 | {}", fmt::join(lines, ", "));
	}

	const std::string Day_1::part_2(const std::filesystem::path& path) const
	{
		return fmt::format("Day 1 Part 2 | Path: {}", (path / "test.text").string());
	}

} // aoc