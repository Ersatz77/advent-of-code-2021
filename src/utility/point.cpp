#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <array>

namespace aoc
{
	// --------------------------------------------------------------------------------
	// Point
	// --------------------------------------------------------------------------------

	const Point Point::origin{ 0, 0 };
	
	std::string Point::to_string() const
	{
		return fmt::format("({},{})", x, y);
	}

	std::array<int, 2> Point::to_array() const
	{
		return { x, y };
	}

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

	Point operator+(const Point& lhs, const Point& rhs)
	{
		return Point(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Point operator-(const Point& lhs, const Point& rhs)
	{
		return Point(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	std::ostream& operator<<(std::ostream& os, const Point& p)
	{
		return os << fmt::format("({},{})", p.x, p.y);
	}

	// --------------------------------------------------------------------------------
	// Vec
	// --------------------------------------------------------------------------------

	const Vec Vec::origin{ 0, 0, 0 };

	std::string Vec::to_string() const
	{
		return fmt::format("({},{},{})", x, y, z);
	}

	std::array<int, 3> Vec::to_array() const
	{
		return { x, y, z };
	}

	bool operator==(const Vec& lhs, const Vec& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	bool operator!=(const Vec& lhs, const Vec& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Vec& lhs, const Vec& rhs)
	{
		return lhs.x < rhs.x || lhs.y < rhs.y || lhs.z < rhs.z;
	}

	Vec operator+(const Vec& lhs, const Vec& rhs)
	{
		return Vec(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Vec operator-(const Vec& lhs, const Vec& rhs)
	{
		return Vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	std::ostream& operator<<(std::ostream& os, const Vec& v)
	{
		return os << fmt::format("({},{},{})", v.x, v.y, v.z);
	}

} // aoc