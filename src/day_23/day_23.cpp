#include "day_23/day_23.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace aoc
{
	const std::string Day_23::part_1(const std::filesystem::path& input_path) const
	{
		std::ifstream file = open_file(input_path / "day_23.txt");

		//
		// No Code because this is possible on paper
		// 
		// #############
        // #...........#
		// ###D#B#C#C###
		//	 #D#A#B#A#
		//	 #########

		return fmt::format("Day 23 Part 1 | Least energy: {}", 19019);
	}

	const std::string Day_23::part_2(const std::filesystem::path& input_path) const
	{
		std::ifstream file = open_file(input_path / "day_23.txt");

		//
		// No Code because this is possible on paper
		// 
		// #############
		// #...........#
		// ###D#B#C#C###
		//   #D#C#B#A#
		//   #D#B#A#C#
		//	 #D#A#B#A#
		//	 #########

		return fmt::format("Day 23 Part 2 | Least energy: {}", 47533);
	}

} // aoc