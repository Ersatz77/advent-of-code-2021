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
		std::unordered_set<std::string>& visited_small_caves, const std::string& current_cave, const bool part_2 = false)
	{
		if (current_cave == "end")
			return 1;

		int paths = 0;
		for (const std::string& adj : caves.at(current_cave))
		{
			// Current adjacent cave is a large cave, so we don't need to do anything special
			if (is_upper(adj))
			{
				paths += path(caves, visited_small_caves, adj, part_2);
				continue;
			}

			// Current adjacent cave is a small cave
			// Small caves can only be visited once and are added to the 'visited' set
			if (!visited_small_caves.contains(adj))
			{
				visited_small_caves.insert(adj);
				paths += path(caves, visited_small_caves, adj, part_2);
				visited_small_caves.erase(adj);
			}
			else if (part_2 && adj != "start")
			{
				paths += path(caves, visited_small_caves, adj, false);
			}
		}

		return paths;
	}

	const std::string Day_12::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> caves = parse_input(input_path / "day_12.txt");
		std::unordered_set<std::string> visited_small_caves = { "start" };
		return fmt::format("Day 12 Part 1 | Paths: {}", path(caves, visited_small_caves, "start"));
	}

	const std::string Day_12::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::vector<std::string>> caves = parse_input(input_path / "day_12.txt");
		std::unordered_set<std::string> visited_small_caves = { "start" };
		return fmt::format("Day 12 Part 2 | Paths: {}", path(caves, visited_small_caves, "start", true));
	}

} // aoc