#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
#include "day_6/day_6.h"
#include "day_7/day_7.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <cstdint>
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
        solutions.push_back(new aoc::Day_2);
        solutions.push_back(new aoc::Day_3);
        solutions.push_back(new aoc::Day_4);
        solutions.push_back(new aoc::Day_5);
        solutions.push_back(new aoc::Day_6);
        solutions.push_back(new aoc::Day_7);

        // Run solution for each day
        uint64_t total_runtime = 0;
        for (const aoc::Day* day : solutions)
        {
            // Part 1
            auto part_1_begin = std::chrono::high_resolution_clock::now();
            std::string part_1_output = day->part_1(input_root);
            auto part_1_end = std::chrono::high_resolution_clock::now();
            uint64_t part_1_runtime = std::chrono::duration_cast<std::chrono::milliseconds>(part_1_end - part_1_begin).count();

            // Part 2
            auto part_2_begin = std::chrono::high_resolution_clock::now();
            std::string part_2_output = day->part_2(input_root);
            auto part_2_end = std::chrono::high_resolution_clock::now();
            uint64_t part_2_runtime = std::chrono::duration_cast<std::chrono::milliseconds>(part_2_end - part_2_begin).count();

            // Print results
            std::cout << fmt::format("{} | Runtime: {}ms\n{} | Runtime: {}ms\n", 
                part_1_output, part_1_runtime, part_2_output, part_2_runtime);

            // Add times to total time
            total_runtime += (part_1_runtime + part_2_runtime);
        }

        // Print total runtime
        std::cout << "Total runtime: " << total_runtime << "ms\n";

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