#include "utility/point.h"

namespace aoc
{
	bool operator==(const Point& lhs, const Point& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	bool operator!=(const Point& lhs, const Point& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Point& lhs, const Point& rhs)
	{
		return lhs.x < rhs.x || lhs.y < rhs.y;
	}

} // aoc