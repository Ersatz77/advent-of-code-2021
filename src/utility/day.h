#ifndef AOC_2021_UTILITY_DAY_H
#define AOC_2021_UTILITY_DAY_H

#include <filesystem>
#include <string>

namespace aoc
{
	// An abstract class for a day
	class Day
	{
	public:
		virtual ~Day() = default;
		virtual const std::string part_1(const std::filesystem::path& path) const = 0;
		virtual const std::string part_2(const std::filesystem::path& path) const = 0;
	};

} // aoc

#endif // !AOC_2021_UTILITY_DAY_H
