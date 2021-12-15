#ifndef AOC_2021_UTILITY_UTILITY_H
#define AOC_2021_UTILITY_UTILITY_H

#include "utility/point.h"

#include <utility>
#include <functional>

namespace aoc
{

} // aoc

namespace std
{
	template <>
	struct hash<pair<char, char>>
	{
		std::size_t operator()(const pair<char, char>& p) const
		{
			return ((hash<int>()(p.first)) ^ (hash<int>()(p.second) << 1));
		}
	};

} // std

#endif // !AOC_2021_UTILITY_UTILITY_H
