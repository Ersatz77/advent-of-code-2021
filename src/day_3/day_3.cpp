#include "day_3/day_3.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace aoc
{
	constexpr uint32_t num_bits = 12;

	std::vector<uint32_t> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::vector<uint32_t> binary_numbers;
		for (std::string number; file >> number; )
		{
			binary_numbers.push_back(std::stoi(number, nullptr, 2));
		}

		return binary_numbers;
	}

	std::array<size_t, 2> num_zeros_and_ones(const std::vector<uint32_t>& binary_numbers, const size_t pos)
	{
		size_t zeros = 0;
		size_t ones = 0;
		for (const uint32_t& bin : binary_numbers)
		{
			uint32_t bit_value = (bin & (1 << pos)) >> pos;
			if (bit_value == 0)
				++zeros;
			else
				++ones;
		}

		return { zeros, ones };
	}

	uint32_t life_support_rating(std::vector<uint32_t> binary_numbers, const bool most_common)
	{
		for (int32_t i = num_bits - 1; i >= 0 && binary_numbers.size() > 1; --i)
		{
			// Find the most common bit
			std::array<size_t, 2> results = num_zeros_and_ones(binary_numbers, i);
			uint32_t common = 0;
			if (most_common)
				common = results[0] <= results[1] ? 1 : 0;
			else
				common = results[0] <= results[1] ? 0 : 1;

			// Remove number from vector if they aren't valid
			binary_numbers.erase(std::remove_if(binary_numbers.begin(), binary_numbers.end(),
				[i, common](const auto& bin) { return (bin & (1 << i)) >> i != common; }), binary_numbers.end());
		}

		return binary_numbers.front();
	}

	const std::string Day_3::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<uint32_t> numbers = parse_input(input_path / "day_3.txt");

		// We only need to find the gamma rate because the epsilon rate is just the inverse
		uint32_t gamma_rate = 0;
		for (size_t i = 0; i < num_bits; ++i)
		{
			std::array<size_t, 2> results = num_zeros_and_ones(numbers, i);
			if (results[0] < results[1])
				gamma_rate |= 1 << i;
		}

		return fmt::format("Day 3 Part 1 | Power consumption: {}", gamma_rate * (gamma_rate ^ 0x00000FFF));
	}

	const std::string Day_3::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<uint32_t> numbers = parse_input(input_path / "day_3.txt");
		uint32_t oxygen_rating = life_support_rating(numbers, true);
		uint32_t co2_rating = life_support_rating(numbers, false);

		return fmt::format("Day 3 Part 2 | Life support rating: {}", oxygen_rating * co2_rating);
	}

} // aoc