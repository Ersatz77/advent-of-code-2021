#include "day_10/day_10.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <stack>

namespace aoc
{
	static std::vector<std::string> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<std::string> chunks;
		for (std::string line; std::getline(file, line); )
		{
			chunks.push_back(line);
		}

		return chunks;
	}

	static int64_t score_corrupted(const std::string& chunk)
	{
		std::stack<char> brackets;
		for (const char c : chunk)
		{
			switch (c)
			{
			case '(':
			case '[':
			case '{':
			case '<':
				brackets.push(c);
				break;
			case ')':
				if (brackets.empty() || brackets.top() != '(')
					return 3;
				brackets.pop();
				break;
			case ']':
				if (brackets.empty() || brackets.top() != '[')
					return 57;
				brackets.pop();
				break;
			case '}':
				if (brackets.empty() || brackets.top() != '{')
					return 1197;
				brackets.pop();
				break;
			case '>':
				if (brackets.empty() || brackets.top() != '<')
					return 25137;
				brackets.pop();
				break;
			default:
				break;
			}
		}

		return 0;
	}

	static int64_t score_incomplete(const std::string& chunk)
	{
		std::stack<char> brackets;
		for (const char c : chunk)
		{
			switch (c)
			{
			case '(':
			case '[':
			case '{':
			case '<':
				brackets.push(c);
				break;
			case ')':
				if (brackets.empty() || brackets.top() != '(')
					return 0;
				brackets.pop();
				break;
			case ']':
				if (brackets.empty() || brackets.top() != '[')
					return 0;
				brackets.pop();
				break;
			case '}':
				if (brackets.empty() || brackets.top() != '{')
					return 0;
				brackets.pop();
				break;
			case '>':
				if (brackets.empty() || brackets.top() != '<')
					return 0;
				brackets.pop();
				break;
			default:
				break;
			}
		}

		int64_t score = 0;
		while (!brackets.empty())
		{
			score *= 5;
			switch (brackets.top())
			{
			case '(':
				score += 1;
				break;
			case '[':
				score += 2;
				break;
			case '{':
				score += 3;
				break;
			case '<':
				score += 4;
				break;
			default:
				break;
			}

			brackets.pop();
		}

		return score;
	}

	const std::string Day_10::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::string> chunks = parse_input(input_path / "day_10.txt");

		// Score corrupted chunks
		int64_t score = 0;
		for (const std::string& chunk : chunks)
		{
			score += score_corrupted(chunk);
		}

		return fmt::format("Day 10 Part 1 | Corrupted score: {}", score);
	}

	const std::string Day_10::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::string> chunks = parse_input(input_path / "day_10.txt");

		// Score incomplete chunks
		std::vector<int64_t> incomplete_scores;
		for (const std::string& chunk : chunks)
		{
			int64_t score = score_incomplete(chunk);
			if (score != 0)
			{
				incomplete_scores.push_back(score);
			}
		}

		std::sort(incomplete_scores.begin(), incomplete_scores.end());

		return fmt::format("Day 10 Part 2 | Middle incomplete score: {}", incomplete_scores[incomplete_scores.size() / 2]);
	}

} // aoc