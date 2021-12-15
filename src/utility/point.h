#ifndef AOC_2021_UTILITY_POINT_H
#define AOC_2021_UTILITY_POINT_H

#include <functional>
#include <array>

namespace aoc
{
	class Point
	{
	public:
		std::array<Point, 4> adjacent_cardinal() const;
		std::array<Point, 8> adjacent() const;

		int x;
		int y;

		static const Point origin;
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

#endif // !AOC_2021_UTILITY_POINT_H
