#include "day_8/day_8.h"

#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace aoc
{
	struct Signal_entry
	{
		std::array<std::string, 10> patterns;
		std::array<std::string, 4> output;
	};

	static std::vector<Signal_entry> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<Signal_entry> entries;
		std::vector<std::string> split_line;
		std::string uniques;
		std::string output;
		std::string temp;
		for (std::string line; std::getline(file, line); )
		{
			split_line = split(line, '|');
			uniques = split_line.front();
			output = split_line.back();

			Signal_entry entry;
			std::istringstream uniques_stream(uniques);
			for (size_t i = 0; i < 10 && uniques_stream >> temp; ++i)
			{
				std::sort(temp.begin(), temp.end());
				entry.patterns[i] = temp;
			}

			std::istringstream output_stream(output);
			for (size_t i = 0; i < 4 && output_stream >> temp; ++i)
			{
				std::sort(temp.begin(), temp.end());
				entry.output[i] = temp;
			}

			entries.push_back(entry);
		}

		return entries;
	}

	static size_t common_chars(const std::string& str_1, const std::string& str_2)
	{
		size_t count = 0;
		for (char c : str_1)
		{
			if (str_2.find(c) != std::string::npos)
			{
				++count;
			}
		}

		return count;
	}

	static int64_t get_mapping_value(const std::string& str, std::array<std::string, 10> mappings)
	{
		const auto it = std::find(mappings.begin(), mappings.end(), str);
		if (it == mappings.end())
		{
			return -1;
		}

		return std::distance(mappings.begin(), it);
	}

	static std::array<std::string, 10> create_mappings(const std::array<std::string, 10>& patterns)
	{
		std::array<std::string, 10> mappings = {};

		// 1, 4, 7, 8
		// Used for finding the rest of the numbers
		for (const std::string& p : patterns)
		{
			switch (p.length())
			{
			case 2:
				mappings[1] = p;
				break;
			case 4:
				mappings[4] = p;
				break;
			case 3:
				mappings[7] = p;
				break;
			case 7:
				mappings[8] = p;
				break;
			}
		}

		// 0, 2, 3, 5, 6, 9
		for (const std::string& p : patterns)
		{
			// Skip patterns we have already found
			if (std::find(mappings.begin(), mappings.end(), p) != mappings.end())
			{
				continue;
			}

			if (p.length() == 5)
			{
				// 2, 3, 5
				if (common_chars(p, mappings[1]) == 2)
				{
					// 2 characters in common with 1
					mappings[3] = p;
				}
				else if (common_chars(p, mappings[4]) == 3)
				{
					// 3 characters in common with 4
					mappings[5] = p;
				}
				else
				{
					mappings[2] = p;
				}
			}
			else
			{
				// 0, 6, 9
				if (common_chars(p, mappings[4]) == 4)
				{
					// 4 characters in common with 4
					mappings[9] = p;
				}
				else if (common_chars(p, mappings[7]) == 2)
				{
					// 2 characters in common with 7
					mappings[6] = p;
				}
				else
				{
					mappings[0] = p;
				}
			}
		}

		return mappings;
	}

	const std::string Day_8::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<Signal_entry> entries = parse_input(input_path / "day_8.txt");

		uint64_t unique_outputs = 0;
		for (const auto& entry : entries)
		{
			for (const auto& output : entry.output)
			{
				if (output.length() == 2 || output.length() == 4 || output.length() == 3 || output.length() == 7)
				{
					++unique_outputs;
				}
			}
		}

		return fmt::format("Day 8 Part 1 | Unique outputs: {}", unique_outputs);
	}

	const std::string Day_8::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<Signal_entry> entries = parse_input(input_path / "day_8.txt");

		int64_t sum = 0;
		for (const Signal_entry& entry : entries)
		{
			std::array<std::string, 10> mappings = create_mappings(entry.patterns);
			std::array<int64_t, 4> output = {};
			for (size_t i = 0; i < entry.output.size(); ++i)
			{
				for (const auto& mapping : mappings)
				{
					if (entry.output[i] == mapping)
					{
						output[i] = get_mapping_value(mapping, mappings);
						break;
					}
				}
			}

			sum += (output[0] * 1000LL) + (output[1] * 100LL) + (output[2] * 10LL) + output[3];
		}

		return fmt::format("Day 8 Part 2 | Output sum: {}", sum);
	}

} // aoc