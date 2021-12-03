#include "day_3/day_3.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <bitset>

namespace aoc
{
	constexpr int num_bits = 12;

	std::vector<std::bitset<num_bits>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::vector<std::bitset<num_bits>> binary_numbers;
		for (std::string line; file >> line; )
		{
			binary_numbers.push_back(std::bitset<num_bits>(line));
		}

		return binary_numbers;
	}

	std::bitset<num_bits> oxygen_generator_rating(const std::vector<std::bitset<num_bits>>& binary_numbers)
	{
		std::vector<std::bitset<num_bits>> valid_numbers = binary_numbers;
		for (size_t i = 0; i < num_bits; ++i)
		{
			// Break out of loop if one number is left
			if (valid_numbers.size() == 1)
				break;

			// Create an offset because indexing position 0 of a 'std::bitset' is the most significant bit and we need the least significant first
			size_t offset = (num_bits - 1) - i;

			// Find the most common bit
			size_t num_zeros = std::count_if(valid_numbers.begin(), valid_numbers.end(), 
				[offset](const auto& bin) { return bin[offset] == 0; });
			size_t num_ones = std::count_if(valid_numbers.begin(), valid_numbers.end(), 
				[offset](const auto& bin) { return bin[offset] == 1; });
			int most_common = num_zeros <= num_ones ? 1 : 0;

			// Copy all new valid numbers to a temp vector then override the vector with previously valid numbers
			std::vector<std::bitset<num_bits>> temp_valid_numbers;
			std::copy_if(valid_numbers.begin(), valid_numbers.end(), std::back_inserter(temp_valid_numbers),
				[offset, most_common](const auto& bin) { return static_cast<int>(bin[offset]) == most_common; });

			valid_numbers = temp_valid_numbers;
		}

		return valid_numbers.front();
	}

	std::bitset<num_bits> co2_scrubber_rating(const std::vector<std::bitset<num_bits>>& binary_numbers)
	{
		std::vector<std::bitset<num_bits>> valid_numbers = binary_numbers;
		for (size_t i = 0; i < num_bits; ++i)
		{
			// Break out of loop if one number is left
			if (valid_numbers.size() == 1)
				break;

			// Create an offset because indexing position 0 of a 'std::bitset' is the most significant bit and we need the least significant first
			size_t offset = (num_bits - 1) - i;

			// Find the least common bit
			size_t num_zeros = std::count_if(valid_numbers.begin(), valid_numbers.end(), 
				[offset](const auto& bin) { return bin[offset] == 0; });
			size_t num_ones = std::count_if(valid_numbers.begin(), valid_numbers.end(), 
				[offset](const auto& bin) { return bin[offset] == 1; });
			int least_common = num_zeros <= num_ones ? 0 : 1;

			// Copy all new valid numbers to a temp vector then override the vector with previously valid numbers 
			std::vector<std::bitset<num_bits>> temp_valid_numbers;
			std::copy_if(valid_numbers.begin(), valid_numbers.end(), std::back_inserter(temp_valid_numbers),
				[offset, least_common](const auto& bin) { return static_cast<int>(bin[offset]) == least_common; });

			valid_numbers = temp_valid_numbers;
		}

		return valid_numbers.front();
	}

	const std::string Day_3::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<std::bitset<num_bits>> numbers = parse_input(input_path / "day_3.txt");

		// We only need to find the gamma rate because the epsilon rate is just the inverse
		std::bitset<num_bits> gamma_rate;
		for (size_t i = 0; i < num_bits; ++i)
		{
			size_t num_zeros = std::count_if(numbers.begin(), numbers.end(), 
				[i](const auto& bin) { return bin[i] == 0; });
			size_t num_ones = std::count_if(numbers.begin(), numbers.end(), 
				[i](const auto& bin) { return bin[i] == 1; });
			gamma_rate[i] = num_zeros > num_ones ? 0 : 1;
		}

		return fmt::format("Day 3 Part 1 | Power consumption: {}", gamma_rate.to_ullong() * gamma_rate.flip().to_ullong());
	}

	const std::string Day_3::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<std::bitset<num_bits>> numbers = parse_input(input_path / "day_3.txt");
		std::bitset<num_bits> oxygen_rating = oxygen_generator_rating(numbers);
		std::bitset<num_bits> co2_rating = co2_scrubber_rating(numbers);

		return fmt::format("Day 3 Part 2 | Life support rating: {}", oxygen_rating.to_ullong() * co2_rating.to_ullong());
	}

} // aoc