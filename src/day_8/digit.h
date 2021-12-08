#ifndef AOC_2021_DAY_8_DIGIT_H
#define AOC_2021_DAY_8_DIGIT_H

#include <iostream>
#include <cstdint>
#include <string>

namespace aoc
{
	class Digit
	{
	public:
		Digit();
		explicit Digit(const std::string& str);

		size_t segments() const;
		size_t common_segments(const Digit& other) const;

		friend std::ostream& operator<<(std::ostream& os, const Digit& d);
		friend bool operator==(const Digit& lhs, const Digit& rhs);
		friend bool operator!=(const Digit& lhs, const Digit& rhs);

	private:
		uint8_t m_segments;
	};

} // aoc

#endif // !AOC_2021_DAY_8_DIGIT_H
