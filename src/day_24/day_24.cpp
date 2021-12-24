#include "day_24/day_24.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/utility.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <utility>

namespace aoc
{
	static std::vector<std::array<std::string, 17>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::vector<std::array<std::string, 17>> instruction_blocks;
		std::string line;
		for (std::string inp_line; std::getline(file, inp_line); )
		{
			std::array<std::string, 17> block = {};
			for (size_t i = 0; i < 17; ++i)
			{
				std::getline(file, line);
				block[i] = line;
			}

			instruction_blocks.push_back(block);
		}
		return instruction_blocks;
	}

	static std::pair<int64_t, int64_t> run(const std::vector<std::array<std::string, 17>>& instruction_blocks)
	{
		std::array<int64_t, 14> max = {};
		std::array<int64_t, 14> min = {};
		std::stack<std::pair<int64_t, int64_t>> z_stack;
		for (size_t idx = 0; idx < instruction_blocks.size(); ++idx)
		{
			int64_t z_div = std::stoull(split(instruction_blocks[idx][3], ' ').back());
			if (z_div == 1)
			{
				z_stack.push(std::make_pair(idx, std::stoull(split(instruction_blocks[idx][14], ' ').back())));
			}
			else if (z_div == 26)
			{
				auto& [prev_idx, x] = z_stack.top();
				z_stack.pop();

				int64_t diff = x + std::stoull(split(instruction_blocks[idx][4], ' ').back());
				int64_t temp_idx = idx;
				if (diff < 0)
				{
					std::swap(temp_idx, prev_idx);
					diff = -diff;
				}

				max[temp_idx] = 9;
				max[prev_idx] = 9 - diff;
				min[temp_idx] = 1 + diff;
				min[prev_idx] = 1;
			}
		}

		return std::make_pair(array_to_int(min), array_to_int(max));
	}

	const std::string Day_24::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::array<std::string, 17>> instruction_blocks = parse_input(input_path / "day_24.txt");
		const auto& [min, max] = run(instruction_blocks);
		return fmt::format("Day 24 Part 1 | Highest model number: {}", max);
	}

	const std::string Day_24::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::array<std::string, 17>> instruction_blocks = parse_input(input_path / "day_24.txt");
		const auto& [min, max] = run(instruction_blocks);
		return fmt::format("Day 24 Part 2 | Lowest model number: {}", min);
	}

} // aoc