#include "day_18/token.h"

#include <vector>

namespace aoc
{
	bool operator==(const Token& lhs, const Token& rhs)
	{
		return lhs.type == rhs.type && lhs.value == rhs.value;
	}

} // aoc