#include "day_1/day_1.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::runtime_error("A path to a folder with inputs is required");
        }

        std::filesystem::path input_root = argv[1];

        // Create a list of solutions
        std::vector<aoc::Day*> solutions;
        solutions.reserve(25);
        solutions.push_back(new aoc::Day_1);

        // Run solution for each day
        for (const aoc::Day* day : solutions)
        {
            // Part 1
            const auto part_1_begin = std::chrono::high_resolution_clock::now();
            const std::string part_1_output = day->part_1(input_root);
            const auto part_1_end = std::chrono::high_resolution_clock::now();

            // Part 2
            const auto part_2_begin = std::chrono::high_resolution_clock::now();
            const std::string part_2_output = day->part_2(input_root);
            const auto part_2_end = std::chrono::high_resolution_clock::now();

            // Print results
            std::cout << fmt::format("{} | Runtime: {}ms\n{} | Runtime: {}ms\n", 
                part_1_output, std::chrono::duration_cast<std::chrono::milliseconds>(part_1_end - part_1_begin).count(),
                part_2_output, std::chrono::duration_cast<std::chrono::milliseconds>(part_2_end - part_2_begin).count());
        }

        // Delete all solutions from vector
        for (const aoc::Day* day : solutions)
        {
            delete day;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << fmt::format("Error: {}\n", e.what());
        return 1;
    }

    return 0;
}