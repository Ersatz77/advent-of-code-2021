#include "day_22/cube.h"

#include <algorithm>
#include <cstdint>
#include <optional>

namespace aoc
{
	int64_t Cube::volume() const
	{
		return (max_x - min_x + 1) * (max_y - min_y + 1) * (max_z - min_z + 1);
	}

	std::optional<Cube> Cube::intersection(const Cube& other) const
	{
		int64_t imin_x = std::max(min_x, other.min_x);
		int64_t imin_y = std::max(min_y, other.min_y);
		int64_t imin_z = std::max(min_z, other.min_z);

		int64_t imax_x = std::min(max_x, other.max_x);
		int64_t imax_y = std::min(max_y, other.max_y);
		int64_t imax_z = std::min(max_z, other.max_z);

		if (imin_x <= imax_x && imin_y <= imax_y && imin_z <= imax_z)
		{
			return Cube{ imin_x, imax_x, imin_y, imax_y, imin_z, imax_z };
		}

		return std::nullopt;
	}

	bool operator==(const Cube& lhs, const Cube& rhs)
	{
		return lhs.min_x == rhs.min_x && lhs.max_x == rhs.max_x &&
			lhs.min_y == rhs.min_y && lhs.max_y == rhs.max_y &&
			lhs.min_z == rhs.min_z && lhs.max_z == rhs.max_z;
	}

	Cube Reboot_step::to_cube() const
	{
		return Cube{ min_x, max_x, min_y, max_y, min_z, max_z };
	}

} // aoc