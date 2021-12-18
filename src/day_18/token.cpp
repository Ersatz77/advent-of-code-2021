#include "day_18/token.h"

#include <vector>

namespace aoc
{
	bool operator==(const Token& lhs, const Token& rhs)
	{
		return lhs.type == rhs.type && lhs.value == rhs.value;
	}

	std::vector<Token> add_expressions(const std::vector<Token>& lhs, const std::vector<Token>& rhs)
	{
		std::vector<Token> output = lhs;
		output.insert(output.end(), rhs.begin(), rhs.end());
		output.insert(output.begin(), Token{ 0, Token_type::OPENING_BRACKET });
		output.insert(output.end(), Token{ 0, Token_type::CLOSING_BRACKET });

		return output;
	}

} // aoc