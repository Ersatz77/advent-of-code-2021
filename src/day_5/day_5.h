#ifndef AOC_2021_DAY_5_H
#define AOC_2021_DAY_5_H

#include "utility/day.h"

#include <filesystem>
#include <string>

namespace aoc
{
	class Day_5 : public Day
	{
	public:
		Day_5() = default;
		const std::string part_1(const std::filesystem::path& input_path) const override;
		const std::string part_2(const std::filesystem::path& input_path) const override;
	};

} // aoc

#endif // !AOC_2021_DAY_5_H