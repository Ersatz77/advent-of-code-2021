#include "day_13/day_13.h"

#include "utility/io.h"
#include "utility/point.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <unordered_set>

namespace aoc
{
	enum class Fold_direction
	{
		X = 0,
		Y,
		UNKNOWN
	};

	struct Fold
	{
		Fold_direction direction;
		int index;
	};

	static void parse_input(const std::filesystem::path& path, std::unordered_set<Point>& points, std::vector<Fold>& folds)
	{
		std::ifstream file = open_file(path);

		int x = 0;
		int y = 0;
		for (std::string line; std::getline(file, line) && !line.empty(); )
		{
			std::istringstream line_stream(line);

			line_stream >> x;
			line_stream.ignore(1);
			line_stream >> y;
			points.insert(Point{ x, y });
		}

		int index = 0;
		Fold_direction direction = Fold_direction::UNKNOWN;
		for (std::string line; std::getline(file, line) && !line.empty(); )
		{
			std::vector<std::string> split_fold = split(line, '=');
			std::istringstream index_stream(split_fold.back());

			index_stream >> index;
			switch (split_fold.front().back())
			{
			case 'x':
				direction = Fold_direction::X;
				break;
			case 'y':
				direction = Fold_direction::Y;
				break;
			default:
				direction = Fold_direction::UNKNOWN;
				break;
			}

			folds.emplace_back(direction, index);
		}
	}

	static std::string print(const std::unordered_set<Point>& points)
	{
		int max_x = std::numeric_limits<int>::min();
		int max_y = std::numeric_limits<int>::min();
		for (const Point& p : points)
		{
			max_x = std::max(max_x, p.x);
			max_y = std::max(max_y, p.y);
		}

		std::string output;
		for (int y = 0; y <= max_y; ++y)
		{
			for (int x = 0; x <= max_x; ++x)
			{
				output += (points.contains(Point{ x, y }) ? '#' : ' ');
			}

			if (y < max_y)
			{
				output += '\n';
			}
		}

		return output;
	}

	static std::unordered_set<Point> fold_y(const std::unordered_set<Point>& points, const int index)
	{
		std::unordered_set<Point> new_points;
		for (const Point& p : points)
		{
			if (p.y > index)
			{
				int y = p.y - ((p.y - index) * 2);
				new_points.insert(Point{ p.x, y });
			}
			else if (p.y < index)
			{
				new_points.insert(p);
			}
		}

		return new_points;
	}

	static std::unordered_set<Point> fold_x(const std::unordered_set<Point>& points, const int index)
	{
		std::unordered_set<Point> new_points;
		for (const Point& p : points)
		{
			if (p.x > index)
			{
				int x = p.x - ((p.x - index) * 2);
				new_points.insert(Point{ x, p.y });
			}
			else if (p.x < index)
			{
				new_points.insert(p);
			}
		}

		return new_points;
	}

	const std::string Day_13::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_set<Point> points;
		std::vector<Fold> folds;
		parse_input(input_path / "day_13.txt", points, folds);

		Fold fold = folds.front();
		switch (fold.direction)
		{
		case Fold_direction::X:
			points = fold_x(points, fold.index);
			break;
		case Fold_direction::Y:
			points = fold_y(points, fold.index);
			break;
		default:
			break;
		}

		return fmt::format("Day 13 Part 1 | Dots: {}", points.size());
	}

	const std::string Day_13::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_set<Point> points;
		std::vector<Fold> folds;
		parse_input(input_path / "day_13.txt", points, folds);

		for (const Fold& f : folds)
		{
			switch (f.direction)
			{
			case Fold_direction::X:
				points = fold_x(points, f.index);
				break;
			case Fold_direction::Y:
				points = fold_y(points, f.index);
				break;
			default:
				break;
			}
		}

		return fmt::format("Day 13 Part 2 | Activation code:\n{}", print(points));
	}

} // aoc