#ifndef AOC_2021_UTILITY_UTILITY_H
#define AOC_2021_UTILITY_UTILITY_H

#include <functional>
#include <cstdint>
#include <tuple>
#include <utility>

namespace aoc
{
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

} // aoc

namespace std
{
	template <>
	struct hash<pair<char, char>>
	{
		std::size_t operator()(const pair<char, char>& p) const
		{
			size_t seed = 0;
			aoc::hash_combine(seed, p.first);
			aoc::hash_combine(seed, p.second);
			return seed;
		}
	};

} // std

#endif // !AOC_2021_UTILITY_UTILITY_H
