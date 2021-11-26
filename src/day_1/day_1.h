#ifndef AOC_2021_DAY_1_H
#define AOC_2021_DAY_1_H

#include "utility/day.h"

#include <filesystem>

namespace aoc
{
	class Day_1 : public Day
	{
	public:
		Day_1() = default;
		~Day_1() = default;
		const std::string part_1(const std::filesystem::path& path) const override;
		const std::string part_2(const std::filesystem::path& path) const override;
	};

} // aoc

#endif // !AOC_2021_DAY_1_H
