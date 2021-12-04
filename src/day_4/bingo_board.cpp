#include "day_4/bingo_board.h"

#include <algorithm>
#include <vector>

namespace aoc
{
	void Bingo_board::add_row(const std::vector<Square>& row)
	{
		m_squares.push_back(row);
	}

	void Bingo_board::mark_square(const int number)
	{
		for (auto& row : m_squares)
		{
			const auto it = std::find_if(row.begin(), row.end(), [number](const Square& sq) { return sq.number == number; });
			if (it != row.end())
			{
				it->marked = true;
			}
		}
	}

	bool Bingo_board::winner() const
	{
		// Row
		for (const auto& row : m_squares)
		{
			size_t num_marked = 0;
			for (const auto& sq : row)
			{
				if (sq.marked)
				{
					++num_marked;
				}
			}

			if (num_marked == row.size())
			{
				return true;
			}
		}

		// Column
		for (size_t i = 0; i < m_squares.size(); ++i)
		{
			size_t num_marked = 0;
			for (const auto& row : m_squares)
			{
				if (row[i].marked)
				{
					++num_marked;
				}
			}

			if (num_marked == m_squares.size())
			{
				return true;
			}
		}

		return false;
	}

	int Bingo_board::sum_of_unmarked() const
	{
		int score = 0;
		for (const auto& row : m_squares)
		{
			for (const auto& sq : row)
			{
				if (!sq.marked)
				{
					score += sq.number;
				}
			}
		}

		return score;
	}

} // aoc