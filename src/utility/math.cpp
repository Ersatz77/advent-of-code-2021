#include "utility/math.h"

namespace aoc
{
	int manhattan_distance_point(const Point& p1, const Point& p2)
	{
		return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
	}

	int manhattan_distance_vec(const Vec& v1, const Vec& v2)
	{
		return std::abs(v1.x - v2.x) + std::abs(v1.y - v2.y) + std::abs(v1.z - v2.z);
	}

} // aoc