#ifndef AOC_2021_UTILITY_UTILITY_H
#define AOC_2021_UTILITY_UTILITY_H

#include <functional>
#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <type_traits>

namespace aoc
{
	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
	T vec_to_int(const std::vector<T> vec)
	{
		T value = 0;
		for (const T i : vec)
		{
			value *= 10;
			value += i;
		}

		return value;
	}

	template<typename T, size_t N, typename = std::enable_if_t<std::is_integral_v<T>>>
	T array_to_int(const std::array<T, N> arr)
	{
		T value = 0;
		for (const T i : arr)
		{
			value *= 10;
			value += i;
		}

		return value;
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
