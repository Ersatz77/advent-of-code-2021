#include "day_19/day_19.h"

#include "day_19/scanner.h"
#include "utility/io.h"
#include "utility/math.h"
#include "utility/point.h"

#include "fmt/format.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>


namespace aoc
{
	static std::vector<Scanner> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
	
		std::vector<Scanner> scanners;
		char junk_ch = ' ';
		for (std::string line; std::getline(file, line); )
		{
			if (line.find("scanner") != std::string::npos)
			{
				Scanner scanner;
				for (std::string beacon_line; std::getline(file, beacon_line) && !beacon_line.empty(); )
				{
					int x = 0;
					int y = 0;
					int z = 0;
					std::istringstream beacon_stream(beacon_line);
					beacon_stream >> x >> junk_ch >> y >> junk_ch >> z;
					scanner.beacons.emplace_back(x, y, z);
				}
	
				scanners.push_back(scanner);
			}
		}
	
		return scanners;
	}

	static std::pair<std::unordered_set<Vec>, std::vector<Scanner>> match_beacons(const std::vector<Scanner>& scanners)
	{
		const auto begin_it = scanners.front().beacons.begin();
		const auto end_it = scanners.front().beacons.end();

		std::unordered_set<Vec> all_beacons(begin_it, end_it);
		std::vector<Scanner> matched_scanners;
		std::queue<Scanner> to_match;
		for (const auto& sc : scanners)
		{
			to_match.push(sc);
		}
		
		while (!to_match.empty())
		{
			Scanner current = to_match.front();
			to_match.pop();

			bool matched = false;
			for (int i = 0; i < 6; i++)
			{
				current.change_axis();
				for (int j = 0; j < 4; j++)
				{
					current.rotate_axis();
					if (current.match(all_beacons))
					{
						matched = true;
						current.align();
						for (auto& beacon : current.beacons)
						{
							all_beacons.insert(beacon);
						}

						matched_scanners.push_back(current);
						break;
					}
				}

				if (matched)
					break;
			}

			if (!matched)
			{
				current.axis = 0;
				to_match.push(current);
			}
		}

		return std::make_pair(all_beacons, matched_scanners);
	}

	const std::string Day_19::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<Scanner> scanners = parse_input(input_path / "day_19.txt");
		const auto result = match_beacons(scanners);
		
		return fmt::format("Day 19 Part 1 | Beacons: {}", result.first.size());
	}

	const std::string Day_19::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<Scanner> scanners = parse_input(input_path / "day_19.txt");
		const auto result = match_beacons(scanners);

		int distance = std::numeric_limits<int>::min();
		for (const auto& lhs : result.second)
		{
			for (const auto& rhs : result.second)
			{
				distance = std::max(distance, manhattan_distance_vec(lhs.pos, rhs.pos));
			}
		}

		return fmt::format("Day 19 Part 2 | Largest distance: {}", distance);
	}

} // aoc