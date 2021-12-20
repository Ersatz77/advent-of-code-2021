#include "day_20/day_20.h"

#include "utility/io.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <string>
#include <array>
#include <unordered_set>

namespace aoc
{
	static void parse_input(const std::filesystem::path path, std::string& enhancement_alg, std::unordered_set<Point>& light_pixels)
	{
		std::ifstream file = open_file(path);
		
		std::getline(file, enhancement_alg);
		file.ignore(1);

		int y = 0;
		for (std::string line; std::getline(file, line); )
		{
			int x = 0;
			std::istringstream line_stream(line);
			for (char pixel = ' '; line_stream >> pixel; )
			{
				if (pixel == '#')
				{
					light_pixels.emplace(x, y);
				}
				++x;
			}

			++y;
		}
	}

	static void step(std::unordered_set<Point>& lit_pixels, const std::string& enhancement_algorithm, const size_t steps)
	{
		for (size_t step = 0; step < steps; ++step)
		{
			std::unordered_set<Point> temp_lit_pixels;
			int min_x = std::numeric_limits<int>::max();
			int max_x = std::numeric_limits<int>::min();
			int min_y = std::numeric_limits<int>::max();
			int max_y = std::numeric_limits<int>::min();
			for (const auto& p : lit_pixels)
			{
				min_x = std::min(min_x, p.x);
				max_x = std::max(max_x, p.x);
				min_y = std::min(min_y, p.y);
				max_y = std::max(max_y, p.y);
			}

			for (int y = min_y - 1; y <= max_y + 1; ++y)
			{
				for (int x = min_x - 1; x <= max_x + 1; ++x)
				{
					size_t alg_offset = 0;
					constexpr std::array<std::array<int, 2>, 9> offsets = { {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}} };
					for (size_t i = 0; i < offsets.size(); ++i)
					{
						int offset_x = x + offsets[i][0];
						int offset_y = y + offsets[i][1];
						bool has_offset = lit_pixels.contains(Point{ offset_x, offset_y });
						bool in_grid = (offset_y >= min_y && offset_y <= max_y && offset_x >= min_x && offset_x <= max_x);

						alg_offset <<= 1;
						if (step % 2 == 0)
						{
							alg_offset |= has_offset ? 1ULL : 0ULL;
						}
						else
						{
							if (in_grid || enhancement_algorithm[0] == '.')
							{
								alg_offset |= has_offset ? 1ULL : 0ULL;
							}
							else
							{
								alg_offset |= 1ULL;
							}
						}
					}

					if (enhancement_algorithm[alg_offset] == '#')
					{
						temp_lit_pixels.emplace(x, y);
					}
				}
			}

			lit_pixels = std::move(temp_lit_pixels);
		}
	}

	const std::string Day_20::part_1(const std::filesystem::path& input_path) const
	{
		std::string enhancement_alg;
		std::unordered_set<Point> lit_pixels;
		parse_input(input_path / "day_20.txt", enhancement_alg, lit_pixels);
		step(lit_pixels, enhancement_alg, 2);

		return fmt::format("Day 20 Part 1 | Lit pixels after 2 steps: {}", lit_pixels.size());
	}

	const std::string Day_20::part_2(const std::filesystem::path& input_path) const
	{
		std::string enhancement_alg;
		std::unordered_set<Point> lit_pixels;
		parse_input(input_path / "day_20.txt", enhancement_alg, lit_pixels);
		step(lit_pixels, enhancement_alg, 50);

		return fmt::format("Day 20 Part 2 | Lit pixels after 50 steps: {}", lit_pixels.size());
	}

} // aoc