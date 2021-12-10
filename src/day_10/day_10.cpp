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
#include <unordered_map>

namespace aoc
{
	static const std::unordered_map<char, char> bracket_table = {
		{'(', ')'},
		{'[', ']'},
		{'{', '}'},
		{'<', '>'}
	};

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

	static std::string create_ending(std::stack<char> brackets)
	{
		std::string ending;
		while (!brackets.empty())
		{
			ending += bracket_table.at(brackets.top());
			brackets.pop();
		}

		return ending;
	}

	const std::string Day_10::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::string> chunks = parse_input(input_path / "day_10.txt");

		// Get all invalid closing brackets
		std::vector<char> invalids;
		for (const std::string& chunk : chunks)
		{
			std::stack<char> brackets;
			for (const char c : chunk)
			{
				if (bracket_table.count(c) > 0)
				{
					brackets.push(c);
					continue;
				}

				if (c != bracket_table.at(brackets.top()))
				{
					invalids.push_back(c);
					break;
				}

				brackets.pop();
			}
		}

		int64_t score = std::count(invalids.begin(), invalids.end(), ')') * 3;
		score += std::count(invalids.begin(), invalids.end(), ']') * 57;
		score += std::count(invalids.begin(), invalids.end(), '}') * 1197;
		score += std::count(invalids.begin(), invalids.end(), '>') * 25137;

		return fmt::format("Day 10 Part 1 | Corrupted score: {}", score);
	}

	const std::string Day_10::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::string> chunks = parse_input(input_path / "day_10.txt");

		// Find incomplete chunks and score them
		std::vector<int64_t> ending_scores;
		for (const std::string& chunk : chunks)
		{
			bool is_corrupted = false;
			std::stack<char> brackets;
			for (const char c : chunk)
			{
				if (bracket_table.count(c) > 0)
				{
					brackets.push(c);
					continue;
				}

				if (c != bracket_table.at(brackets.top()))
				{
					is_corrupted = true;
					break;
				}

				brackets.pop();
			}

			// Score incomplete chunks
			if (!is_corrupted)
			{
				int64_t score = 0;
				for (const char c : create_ending(brackets))
				{
					score *= 5;
					switch (c)
					{
					case ')':
						score += 1;
						break;
					case ']':
						score += 2;
						break;
					case '}':
						score += 3;
						break;
					case '>':
						score += 4;
						break;
					default:
						break;
					}
				}

				ending_scores.push_back(score);
			}
		}

		std::sort(ending_scores.begin(), ending_scores.end());

		return fmt::format("Day 10 Part 2 | Middle ending score: {}", ending_scores[ending_scores.size() / 2]);
	}

} // aoc