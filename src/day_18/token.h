#ifndef AOC_2021_DAY_18_TOKEN_H
#define AOC_2021_DAY_18_TOKEN_H

#include <vector>

namespace aoc
{
	enum class Token_type
	{
		NUMBER = 0,
		OPENING_BRACKET,
		CLOSING_BRACKET
	};

	struct Token
	{
		int8_t value;
		Token_type type;
	};

	bool operator==(const Token& lhs, const Token& rhs);

} // aoc

#endif // !AOC_2021_DAY_18_TOKEN_H
