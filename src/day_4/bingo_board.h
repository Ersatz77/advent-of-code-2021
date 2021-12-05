#ifndef AOC_2021_DAY_4_BINGO_BOARD_H
#define AOC_2021_DAY_4_BINGO_BOARD_H

#include <iostream>
#include <array>

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

		void mark_square(const int number);
		bool winner() const;
		int sum_of_unmarked() const;

		friend std::istream& operator>>(std::istream& is, Bingo_board& board);

	private:
		bool winning_row(const size_t row) const;
		bool winning_column(const size_t column) const;

		std::array<std::array<Square, 5>, 5> m_squares = {};
	};

}// aoc

#endif // !AOC_2021_DAY_4_BINGO_BOARD_H
