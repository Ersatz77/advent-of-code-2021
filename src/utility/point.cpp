#include "utility/point.h"

#include <iostream>
#include <array>

namespace aoc
{
	std::array<Point, 4> Point::adjacent_cardinal() const
	{
		std::array<Point, 4> adjacent = {};
		constexpr std::array<int, 8> offsets = { 0, 1, 0, -1, 1, 0, -1, 0 };
		size_t adj_idx = 0;
		for (size_t i = 1; i < offsets.size(); i += 2)
		{
			int dx = x + offsets[i - 1];
			int dy = y + offsets[i];
			adjacent[adj_idx].x = dx;
			adjacent[adj_idx].y = dy;
			++adj_idx;
		}

		return adjacent;
	}

	std::array<Point, 8> Point::adjacent() const
	{
		std::array<Point, 8> adjacent = {};
		constexpr std::array<int, 16> offsets = { 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1, 0, 1, 1, 1 };
		size_t adj_idx = 0;
		for (size_t i = 1; i < offsets.size(); i += 2)
		{
			int dx = x + offsets[i - 1];
			int dy = y + offsets[i];
			adjacent[adj_idx].x = dx;
			adjacent[adj_idx].y = dy;
			++adj_idx;
		}

		return adjacent;
	}

	const Point Point::origin{ 0, 0 };

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

	std::ostream& operator<<(std::ostream& os, const Point& p)
	{
		return os << '(' << p.x << ',' << p.y << ')';
	}

} // aoc