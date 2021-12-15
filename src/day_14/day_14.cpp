#include "day_14/day_14.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>

namespace aoc
{
	static void parse_input(const std::filesystem::path& path, std::unordered_map<std::string, int64_t>& polymer, 
		std::pair<char, char>& end_elements, std::unordered_map<std::string, char>& rules)
	{
		std::ifstream file = open_file(path);

		std::string poly;
		std::getline(file, poly);

		end_elements.first = poly.front();
		end_elements.second = poly.back();
		for (size_t i = 1; i < poly.length(); ++i)
		{
			++polymer[poly.substr(i - 1, 2)];
		}

		file.ignore(1);
		for (std::string line; std::getline(file, line) && !line.empty(); )
		{
			rules[line.substr(0, 2)] = line[6];
		}
	}

	std::unordered_map<std::string, int64_t> react(const std::unordered_map<std::string, int64_t>& polymer, 
		std::unordered_map<std::string, char>& rules)
	{
		std::unordered_map<std::string, int64_t> new_polymer;
		for (const auto& [compound, amount] : polymer)
		{
			const auto rule_it = rules.find(compound);
			if (rule_it != rules.end())
			{
				std::string left(1, compound.front());
				std::string right(1, rule_it->second);

				left += rule_it->second;
				right += compound.back();

				new_polymer[left] += amount;
				new_polymer[right] += amount;
			}
			else
			{
				new_polymer[compound] += amount;
			}
		}

		return new_polymer;
	}

	int64_t score(const std::unordered_map<std::string, int64_t>& polymer, const std::pair<char, char>& end_elements)
	{
		std::unordered_map<char, int64_t> elements;
		++elements[end_elements.first];
		++elements[end_elements.second];
		for (const auto& [compound, amount] : polymer)
		{
			elements[compound.front()] += amount;
			elements[compound.back()] += amount;
		}

		int64_t min = std::numeric_limits<int64_t>::max();
		int64_t max = std::numeric_limits<int64_t>::min();
		for (const auto& [element, total] : elements)
		{
			int64_t half_total = total / 2;
			min = std::min(min, half_total);
			max = std::max(max, half_total);
		}

		return max - min;
	}

	const std::string Day_14::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, int64_t> polymer;
		std::pair<char, char> end_elements;
		std::unordered_map<std::string, char> rules;
		parse_input(input_path / "day_14.txt", polymer, end_elements, rules);

		for (size_t i = 0; i < 10; ++i)
		{
			polymer = react(polymer, rules);
		}

		return fmt::format("Day 14 Part 1 | Element difference after 10 reactions: {}", score(polymer, end_elements));
	}

	const std::string Day_14::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, int64_t> polymer;
		std::pair<char, char> end_elements;
		std::unordered_map<std::string, char> rules;
		parse_input(input_path / "day_14.txt", polymer, end_elements, rules);

		for (size_t i = 0; i < 40; ++i)
		{
			polymer = react(polymer, rules);
		}

		return fmt::format("Day 14 Part 2 | Element difference after 40 reactions: {}", score(polymer, end_elements));
	}

} // aoc