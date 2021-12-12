#include "day_12/day_12.h"

#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace aoc
{
	static std::unordered_map<std::string, std::vector<std::string>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_map<std::string, std::vector<std::string>> nodes;
		for (std::string line; std::getline(file, line); )
		{
			std::vector<std::string> ab = split(line, '-');
			nodes[ab.front()].emplace_back(ab.back());
			nodes[ab.back()].emplace_back(ab.front());
		}

		return nodes;
	}

	static int path_p1(const std::unordered_map<std::string, std::vector<std::string>>& nodes, 
		const std::string& current, std::unordered_set<std::string> visited = {})
	{
		if (current == "end")
			return 1;

		if (is_lower(current) && visited.count(current) > 0)
			return 0;

		int paths = 0;
		visited.insert(current);
		for (const std::string& node : nodes.at(current))
		{
			paths += path_p1(nodes, node, visited);
		}

		return paths;
	}

	static int path_p2(const std::unordered_map<std::string, std::vector<std::string>>& nodes,
		const std::string& current, bool duplicate = false, std::unordered_set<std::string> visited = {})
	{
		if (current == "end")
			return 1;

		if (current == "start" && visited.count(current) > 0)
			return 0;

		if (is_lower(current) && visited.count(current) > 0)
		{
			if (!duplicate)
			{
				duplicate = true;
			}
			else
			{
				return 0;
			}
		}

		int paths = 0;
		visited.insert(current);
		for (const std::string& node : nodes.at(current))
		{
			paths += path_p2(nodes, node, duplicate, visited);
		}

		return paths;
	}

	const std::string Day_12::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> nodes = parse_input(input_path / "day_12.txt");
		return fmt::format("Day 12 Part 1 | Paths: {}", path_p1(nodes, "start"));
	}

	const std::string Day_12::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> nodes = parse_input(input_path / "day_12.txt");
		return fmt::format("Day 12 Part 2 | Paths {}", path_p2(nodes, "start"));
	}

} // aoc