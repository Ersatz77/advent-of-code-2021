#include "day_16/day_16.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <string>
#include <list>
#include <iterator>

namespace aoc
{
	static std::list<bool> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::list<bool> bits;
		for (char hex_ch = ' '; file >> hex_ch; )
		{
			int binary = static_cast<int>(hex_ch);
			binary -= (hex_ch >= '0' && hex_ch <= '9') ? 48 : 55;
			for (int i = 3; i >= 0; --i)
			{
				bool bit = (binary & (1 << i)) >> i == 1;
				bits.push_back(bit);
			}
		}

		return bits;
	}

	// Reads 'size' amount of bits as an integer
	static uint64_t read_int(std::list<bool>& bits, const size_t size)
	{
		uint64_t value = 0;
		for (size_t i = 0; i < size; ++i)
		{
			bool bit = bits.front();
			bits.erase(bits.begin());
			value <<= 1;
			value |= bit ? 1 : 0;	
		}

		return value;
	}

	// Reads chunks of bits and contructs an integer out of them
	static uint64_t read_dynamic_int(std::list<bool>& bits)
	{
		uint64_t value = 0;
		uint64_t next_chunk = 0b10000;
		while (next_chunk & 0b10000)
		{
			value <<= 4;
			next_chunk = read_int(bits, 5);
			value |= next_chunk & 0b01111;
		}

		return value;
	}

	// Moves 'amount' number of elements from 'src' and adds them to the beginning of 'dest'
	static void move_elements(std::list<bool>& dest, std::list<bool>& src, const size_t amount)
	{
		auto to_it = src.begin();
		std::advance(to_it, amount);
		dest.splice(dest.begin(), src, src.begin(), to_it);
	}

	// Reads a packet and parses subpackets if needed
	static uint64_t read_packet(std::list<bool>& bits, uint64_t& version_sum)
	{
		version_sum += read_int(bits, 3);
		uint64_t type_id = read_int(bits, 3);

		// Packet is a literal type
		if (type_id == 4)
		{
			return read_dynamic_int(bits);
		}

		// Packet is an operator type, so we need to read every subpacket and collect their outputs
		std::vector<uint64_t> outputs;
		uint64_t length_type_id = read_int(bits, 1);
		if (length_type_id == 0)
		{
			uint64_t total_subpacket_bits = read_int(bits, 15);
			std::list<bool> subpacket_bits;
			move_elements(subpacket_bits, bits, total_subpacket_bits);
			while (!subpacket_bits.empty())
			{
				outputs.push_back(read_packet(subpacket_bits, version_sum));
			}
		}
		else if (length_type_id == 1)
		{
			uint64_t total_subpackets = read_int(bits, 11);
			for (size_t i = 0; i < total_subpackets; ++i)
			{
				outputs.push_back(read_packet(bits, version_sum));
			}
		}

		// Operations on subpacket outputs
		switch (type_id)
		{
		case 0:
			return std::accumulate(outputs.begin(), outputs.end(), 0ULL);
		case 1:
			return std::accumulate(outputs.begin(), outputs.end(), 1ULL, std::multiplies<uint64_t>());
		case 2:
			return *std::min_element(outputs.begin(), outputs.end());
		case 3:
			return *std::max_element(outputs.begin(), outputs.end());
		case 5:
			return (outputs[0] > outputs[1]) ? 1 : 0;
		case 6:
			return (outputs[0] < outputs[1]) ? 1 : 0;
		case 7:
			return (outputs[0] == outputs[1]) ? 1 : 0;
		default:
			return 0;
		}
	}

	const std::string Day_16::part_1(const std::filesystem::path& input_path) const
	{
		std::list<bool> bits = parse_input(input_path / "day_16.txt");
		uint64_t version_sum = 0;
		read_packet(bits, version_sum);
		return fmt::format("Day 16 Part 1 | Version sum: {}", version_sum);
	}

	const std::string Day_16::part_2(const std::filesystem::path& input_path) const
	{
		std::list<bool> bits = parse_input(input_path / "day_16.txt");
		uint64_t version_sum = 0;
		uint64_t output = read_packet(bits, version_sum);
		return fmt::format("Day 16 Part 2 | Output: {}", output);
	}

} // aoc