#ifndef AOC_2021_DAY_4_BINGO_BOARD_H
#define AOC_2021_DAY_4_BINGO_BOARD_H

#include <vector>

namespace aoc
{
	struct Square
	{
		int number;
		bool marked;
	};

	class Bingo_board
	{
	public:
		Bingo_board() = default;

		void add_row(const std::vector<Square>& row);
		void mark_square(const int number);

		bool winner() const;
		int sum_of_unmarked() const;

	private:
		std::vector<std::vector<Square>> m_squares;
	};

}// aoc

#endif // !AOC_2021_DAY_4_BINGO_BOARD_H
