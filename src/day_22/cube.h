#ifndef AOC_2021_DAY_22_CUBE_H
#define AOC_2021_DAY_22_CUBE_H

#include "utility/utility.h"

#include <cstdint>
#include <optional>

namespace aoc
{
	class Cube
	{
	public:
		int64_t volume() const;
		std::optional<Cube> intersection(const Cube& other) const;

		int64_t min_x;
		int64_t max_x;
		int64_t min_y;
		int64_t max_y;
		int64_t min_z;
		int64_t max_z;
	};

	bool operator==(const Cube& lhs, const Cube& rhs);

	enum class Cube_state
	{
		OFF = 0,
		ON = 1
	};

	class Reboot_step
	{
	public:
		Cube to_cube() const;

		Cube_state state;
		int64_t min_x;
		int64_t max_x;
		int64_t min_y;
		int64_t max_y;
		int64_t min_z;
		int64_t max_z;
	};

} // aoc

namespace std
{
	template <>
	struct hash<aoc::Cube>
	{
		std::size_t operator()(const aoc::Cube& c) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, c.min_x);
			aoc::hash_combine(seed, c.max_x);
			aoc::hash_combine(seed, c.min_y);
			aoc::hash_combine(seed, c.max_y);
			aoc::hash_combine(seed, c.min_z);
			aoc::hash_combine(seed, c.max_z);
			return seed;
		}
	};

} // std

#endif // !AOC_2021_DAY_22_CUBE_H
