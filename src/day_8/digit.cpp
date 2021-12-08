#include "day_8/digit.h"

#include <iostream>
#include <cstdint>
#include <string>

namespace aoc
{
	Digit::Digit() :
		m_segments(0)
	{

	}

	Digit::Digit(const std::string& str) :
		m_segments(0)
	{
		for (const char c : str)
		{
			m_segments |= 1 << (static_cast<uint8_t>(c) - 97);
		}
	}

	size_t Digit::segments() const
	{
		size_t num_segments = 0;
		for (size_t i = 0; i < 8; ++i)
		{
			if ((m_segments & (1 << i)) >> i == 1)
			{
				++num_segments;
			}
		}

		return num_segments;
	}

	size_t Digit::common_segments(const Digit& other) const
	{
		uint8_t common = m_segments & other.m_segments;
		size_t num_segments = 0;
		for (size_t i = 0; i < 8; ++i)
		{
			if ((common & (1 << i)) >> i == 1)
			{
				++num_segments;
			}
		}

		return num_segments;
	}

	std::ostream& operator<<(std::ostream& os, const Digit& d)
	{
		for (size_t i = 0; i < 7; ++i)
		{
			if ((d.m_segments & (1 << i)) >> i == 1)
			{
				os << static_cast<char>(i + 97);
			}
		}

		return os;
	}

	bool operator==(const Digit& lhs, const Digit& rhs)
	{
		return lhs.m_segments == rhs.m_segments;
	}

	bool operator!=(const Digit& lhs, const Digit& rhs)
	{
		return !(lhs == rhs);
	}

} // aoc