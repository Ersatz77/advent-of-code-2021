#include "day_18/day_18.h"

#include "day_18/token.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <stack>

namespace aoc
{
	static std::vector<std::vector<Token>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<std::vector<Token>> expressions;
		for (std::string line; std::getline(file, line); )
		{
			std::vector<Token> tokens;
			std::istringstream line_stream(line);
			for (char c = 0; line_stream >> c; )
			{
				switch (c)
				{
				case '[':
					tokens.push_back(Token{ 0, Token_type::OPENING_BRACKET});
					break;
				case ']':
					tokens.push_back(Token{ 0, Token_type::CLOSING_BRACKET });
					break;
				case ',':
					// Comma tokens are unnecessary
					break;
				default:
					tokens.push_back(Token{ static_cast<int8_t>(c - 48), Token_type::NUMBER});
					break;
				}
			}

			expressions.push_back(tokens);
		}

		return expressions;
	}

	static bool explode(std::vector<Token>& expression)
	{
		size_t depth = 0;
		for (size_t pos = 0; pos < expression.size() - 4; ++pos)
		{
			if (depth >= 4 && expression[pos].type == Token_type::OPENING_BRACKET && expression[pos + 3].type == Token_type::CLOSING_BRACKET)
			{
				for (size_t left = pos; left > 0; --left)
				{
					if (expression[left - 1].type == Token_type::NUMBER)
					{
						expression[left - 1].value += expression[pos + 1].value;
						break;
					}
				}

				for (size_t right = pos + 4; right < expression.size(); ++right)
				{
					if (expression[right].type == Token_type::NUMBER)
					{
						expression[right].value += expression[pos + 2].value;
						break;
					}
				}

				expression.erase(expression.begin() + pos, expression.begin() + pos + 4);
				expression.insert(expression.begin() + pos, Token{ 0, Token_type::NUMBER });

				return true;
			}
			else if (expression[pos].type == Token_type::OPENING_BRACKET)
			{
				++depth;
			}
			else if (expression[pos].type == Token_type::CLOSING_BRACKET)
			{
				--depth;
			}
		}

		return false;
	}

	static bool split(std::vector<Token>& expression)
	{
		for (size_t pos = 0; pos < expression.size(); ++pos)
		{
			if (expression[pos].type == Token_type::NUMBER && expression[pos].value >= 10)
			{
				int8_t left = static_cast<int8_t>(std::floor(expression[pos].value / 2.0));
				int8_t right = static_cast<int8_t>(std::ceil(expression[pos].value / 2.0));

				expression.erase(expression.begin() + pos, expression.begin() + pos + 1);
				expression.insert(expression.begin() + pos, Token{ 0, Token_type::OPENING_BRACKET });
				expression.insert(expression.begin() + pos + 1, Token{ left, Token_type::NUMBER });
				expression.insert(expression.begin() + pos + 2, Token{ right, Token_type::NUMBER });
				expression.insert(expression.begin() + pos + 3, Token{ 0, Token_type::CLOSING_BRACKET });

				return true;
			}
		}

		return false;
	}

	static int magnitude(const std::vector<Token>& expression)
	{
		std::stack<int> values;
		for (const auto& t : expression)
		{
			if (t.type == Token_type::NUMBER)
			{
				values.push(t.value);
			}
			else if (t.type == Token_type::CLOSING_BRACKET)
			{
				int right = values.top() * 2;
				values.pop();

				int left = values.top() * 3;
				values.pop();

				values.push(left + right);
			}
		}

		return values.top();
	}

	static std::vector<Token> add_expressions(const std::vector<Token>& lhs, const std::vector<Token>& rhs)
	{
		std::vector<Token> output = lhs;
		output.insert(output.end(), rhs.begin(), rhs.end());
		output.insert(output.begin(), Token{ 0, Token_type::OPENING_BRACKET });
		output.insert(output.end(), Token{ 0, Token_type::CLOSING_BRACKET });

		return output;
	}

	static std::vector<Token> reduce(std::vector<Token> expression)
	{
		while (true)
		{
			if (!explode(expression) && !split(expression))
			{
				break;
			}
		}

		return expression;
	}

	const std::string Day_18::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<Token>> expressions = parse_input(input_path / "day_18.txt");

		for (size_t i = 1; i < expressions.size(); ++i)
		{
			expressions[i] = reduce(add_expressions(expressions[i - 1], expressions[i]));
		}

		return fmt::format("Day 18 Part 1 | Magnitude of sums: {}", magnitude(expressions.back()));
	}

	const std::string Day_18::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::vector<Token>> expressions = parse_input(input_path / "day_18.txt");

		int highest = std::numeric_limits<int>::min();
		for (const auto& left : expressions)
		{
			for (const auto& right : expressions)
			{
				highest = std::max(highest, magnitude(reduce(add_expressions(left, right))));
			}
		}

		return fmt::format("Day 18 Part 2 | Highest magnitude: {}", highest);
	}

} // aoc