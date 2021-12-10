#ifndef AOC_2021_DAY_8_SIGNAL_H
#define AOC_2021_DAY_8_SIGNAL_H

#include "day_8/digit.h"

#include <iostream>
#include <cstdint>
#include <array>

namespace aoc
{
	class Signal
	{
	public:
		Signal() = default;

		size_t unique_outputs() const;
		int64_t decode_output() const;

		friend std::istream& operator>>(std::istream& is, Signal& s);

	private:
		std::array<Digit, 10> create_mappings() const;

		std::array<Digit, 10> m_unique = {};
		std::array<Digit, 4> m_output = {};
	};

} // aoc

#endif // !AOC_2021_DAY_8_SIGNAL_H
