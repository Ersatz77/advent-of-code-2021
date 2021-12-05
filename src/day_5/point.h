#ifndef AOC_2021_DAY_5_POINT_H
#define AOC_2021_DAY_5_POINT_H

#include <functional>

namespace aoc
{
	struct Point
	{
		int x;
		int y;
	};

	bool operator==(const Point& lhs, const Point& rhs);
	bool operator!=(const Point& lhs, const Point& rhs);
	bool operator<(const Point& lhs, const Point& rhs);

} // aoc

namespace std
{
	template <>
	struct hash<aoc::Point>
	{
		std::size_t operator()(const aoc::Point& p) const
		{
			return ((hash<int>()(p.x)) ^ (hash<int>()(p.y) << 1));
		}
	};

} // std

#endif // !AOC_2021_DAY_5_POINT_H
