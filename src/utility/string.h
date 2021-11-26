#ifndef AOC_2021_UTILITY_STRING_H
#define AOC_2021_UTILITY_STRING_H

#include <string>
#include <vector>

namespace aoc
{
	// Split a string using a single delimiter
	std::vector<std::string> split(const std::string& str, const char delim);

	// Split a string using regex
	std::vector<std::string> regex_split(const std::string& str, const std::string& pattern);

} // aoc

#endif // !AOC_2021_UTILITY_STRING_H
