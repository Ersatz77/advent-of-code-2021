#include "day_8/signal.h"

#include "day_8/digit.h"

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <array>
#include <string>

namespace aoc
{
	size_t Signal::unique_outputs() const
	{
		size_t num_unique = 0;
		for (const Digit& d : m_output)
		{
			switch (d.segments())
			{
			case 2:
			case 4:
			case 3:
			case 7:
				++num_unique;
				break;
			default:
				break;
			}
		}

		return num_unique;
	}

	int64_t Signal::decode_output() const
	{
		std::array<Digit, 10> mappings = create_mappings();
		std::array<int64_t, 4> output = {};
		for (size_t i = 0; i < m_output.size(); ++i)
		{
			for (const Digit& mapping : mappings)
			{
				if (m_output[i] == mapping)
				{
					output[i] = get_mapping_index(mapping, mappings);
					break;
				}
			}
		}

		return (output[0] * 1000LL) + (output[1] * 100LL) + (output[2] * 10LL) + output[3];
	}

	std::array<Digit, 10> Signal::create_mappings() const
	{
		std::array<Digit, 10> mappings = {};

		// 1, 4, 7, 8
		// Used for finding the rest of the numbers
		for (const Digit& digit : m_unique)
		{
			switch (digit.segments())
			{
			case 2:
				mappings[1] = digit;
				break;
			case 4:
				mappings[4] = digit;
				break;
			case 3:
				mappings[7] = digit;
				break;
			case 7:
				mappings[8] = digit;
				break;
			default:
				break;
			}
		}

		// 0, 2, 3, 5, 6, 9
		for (const Digit& digit : m_unique)
		{
			if (std::find_if(mappings.begin(), mappings.end(),
				[&digit](const Digit& d) { return d == digit; }) != mappings.end())
			{
				continue;
			}

			if (digit.segments() == 5)
			{
				// 2, 3, 5
				if (digit.common_segments(mappings[1]) == 2)
				{
					// 2 bits in common with 1
					mappings[3] = digit;
				}
				else if (digit.common_segments(mappings[4]) == 3)
				{
					// 3 bits in common with 4
					mappings[5] = digit;
				}
				else
				{
					mappings[2] = digit;
				}
			}
			else
			{
				// 0, 6, 9
				if (digit.common_segments(mappings[4]) == 4)
				{
					// 4 bits in common with 4
					mappings[9] = digit;
				}
				else if (digit.common_segments(mappings[7]) == 2)
				{
					// 2 bits in common with 7
					mappings[6] = digit;
				}
				else
				{
					mappings[0] = digit;
				}
			}
		}

		return mappings;
	}

	size_t Signal::get_mapping_index(const Digit& mapping, const std::array<Digit, 10>& mappings) const
	{
		const auto it = std::find_if(mappings.begin(), mappings.end(), [&mapping](const Digit& d) { return d == mapping; });
		if (it == mappings.end())
		{
			return 11;
		}

		return std::distance(mappings.begin(), it);
	}

	std::istream& operator>>(std::istream& is, Signal& s)
	{
		std::string temp;
		for (size_t i = 0; i < 10; ++i)
		{
			is >> temp;
			s.m_unique[i] = Digit(temp);
		}

		// Get rid of the '|' character
		is >> temp;

		for (size_t i = 0; i < 4; ++i)
		{
			is >> temp;
			s.m_output[i] = Digit(temp);
		}

		return is;
	}

} // aoc