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

		std::unordered_map<std::string, std::vector<std::string>> caves;
		for (std::string connection; std::getline(file, connection); )
		{
			std::vector<std::string> cave_connection = split(connection, '-');
			caves[cave_connection.front()].emplace_back(cave_connection.back());
			caves[cave_connection.back()].emplace_back(cave_connection.front());
		}

		return caves;
	}

	static int path(const std::unordered_map<std::string, std::vector<std::string>>& caves,
		std::unordered_set<std::string>& visited, const std::string& current_cave, const bool part_2 = false)
	{
		if (current_cave == "end")
			return 1;

		int paths = 0;
		for (const std::string& adj : caves.at(current_cave))
		{
			if (!visited.contains(adj))
			{
				if (is_lower(adj))
				{
					visited.insert(adj);
				}

				paths += path(caves, visited, adj, part_2);

				if (is_lower(adj))
				{
					visited.erase(adj);
				}
			}
			else if (part_2 && adj != "start")
			{
				paths += path(caves, visited, adj, false);
			}
		}

		return paths;
	}

	const std::string Day_12::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> caves = parse_input(input_path / "day_12.txt");
		std::unordered_set<std::string> visited = { "start" };
		return fmt::format("Day 12 Part 1 | Paths: {}", path(caves, visited, "start"));
	}

	const std::string Day_12::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> caves = parse_input(input_path / "day_12.txt");
		std::unordered_set<std::string> visited = { "start" };
		return fmt::format("Day 12 Part 2 | Paths: {}", path(caves, visited, "start", true));
	}

} // aoc