#ifndef AOC_2021_UTILITY_POINT_H
#define AOC_2021_UTILITY_POINT_H

#include "utility/utility.h"

#include <iostream>
#include <functional>
#include <string>
#include <array>

namespace aoc
{
	class Point
	{
	public:
		// Returns the 4 (NESW) points around this point
		std::array<Point, 4> adjacent_cardinal() const;

		// Returns all 8 points around this point
		std::array<Point, 8> adjacent() const;

		std::string to_string() const;
		std::array<int, 2> to_array() const;

		Point& operator+=(const Point& other);
		Point& operator-=(const Point& other);
		Point& operator*=(const Point& other);
		Point& operator/=(const Point& other);

		int x;
		int y;

		static const Point origin;
	};

	bool operator==(const Point& lhs, const Point& rhs);
	bool operator!=(const Point& lhs, const Point& rhs);
	bool operator<(const Point& lhs, const Point& rhs);
	bool operator>(const Point& lhs, const Point& rhs);
	Point operator+(const Point& lhs, const Point& rhs);
	Point operator-(const Point& lhs, const Point& rhs);
	Point operator*(const Point& lhs, const Point& rhs);
	Point operator/(const Point& lhs, const Point& rhs);
	std::ostream& operator<<(std::ostream& os, const Point& p);

	class Vec
	{
	public:
		std::string to_string() const;
		std::array<int, 3> to_array() const;

		Vec& operator+=(const Vec& other);
		Vec& operator-=(const Vec& other);
		Vec& operator*=(const Vec& other);
		Vec& operator/=(const Vec& other);

		int x;
		int y;
		int z;

		static const Vec origin;
	};

	bool operator==(const Vec& lhs, const Vec& rhs);
	bool operator!=(const Vec& lhs, const Vec& rhs);
	bool operator<(const Vec& lhs, const Vec& rhs);
	bool operator>(const Vec& lhs, const Vec& rhs);
	Vec operator+(const Vec& lhs, const Vec& rhs);
	Vec operator-(const Vec& lhs, const Vec& rhs);
	Vec operator*(const Vec& lhs, const Vec& rhs);
	Vec operator/(const Vec& lhs, const Vec& rhs);
	std::ostream& operator<<(std::ostream& os, const Vec& v);

} // aoc

namespace std
{
	template <>
	struct hash<aoc::Point>
	{
		std::size_t operator()(const aoc::Point& p) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, p.x);
			aoc::hash_combine(seed, p.y);
			return seed;
		}
	};

	template <>
	struct hash<aoc::Vec>
	{
		std::size_t operator()(const aoc::Vec& v) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, v.x);
			aoc::hash_combine(seed, v.y);
			aoc::hash_combine(seed, v.z);
			return seed;
		}
	};

} // std

#endif // !AOC_2021_UTILITY_POINT_H