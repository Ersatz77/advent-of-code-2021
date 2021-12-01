#ifndef AOC_2021_DAY_2_H
#define AOC_2021_DAY_2_H

#include "utility/day.h"

#include <filesystem>
#include <string>

namespace aoc
{
	class Day_2 : public Day
	{
	public:
		Day_2() = default;
		~Day_2() = default;
		const std::string part_1(const std::filesystem::path& input_path) const override;
		const std::string part_2(const std::filesystem::path& input_path) const override;
	};

} // aoc

#endif // !AOC_2021_DAY_2_H