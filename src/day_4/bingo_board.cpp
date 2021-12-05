#include "day_4/bingo_board.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <array>

namespace aoc
{
	void Bingo_board::mark_square(const int number)
	{
		for (size_t row = 0; row < m_squares.size(); ++row)
		{
			for (size_t column = 0; column < m_squares.front().size(); ++column)
			{
				if (m_squares[row][column].number == number)
				{
					m_squares[row][column].marked = true;
					return;
				}
			}
		}
	}

	bool Bingo_board::winner() const
	{
		for (size_t i = 0; i < m_squares.size(); ++i)
		{
			if (winning_row(i) || winning_column(i))
			{
				return true;
			}
		}

		return false;
	}

	int Bingo_board::sum_of_unmarked() const
	{
		int score = 0;
		for (size_t row = 0; row < m_squares.size(); ++row)
		{
			for (size_t column = 0; column < m_squares.front().size(); ++column)
			{
				if (!m_squares[row][column].marked)
				{
					score += m_squares[row][column].number;
				}
			}
		}

		return score;
	}

	bool Bingo_board::winning_row(const size_t row) const
	{
		size_t num_marked = 0;
		for (size_t column = 0; column < m_squares.front().size(); ++column)
		{
			if (m_squares[row][column].marked)
			{
				++num_marked;
			}
		}

		return num_marked == m_squares.front().size();
	}

	bool Bingo_board::winning_column(const size_t column) const
	{
		size_t num_marked = 0;
		for (size_t row = 0; row < m_squares.size(); ++row)
		{
			if (m_squares[row][column].marked)
			{
				++num_marked;
			}
		}

		return num_marked == m_squares.size();
	}

	std::istream& operator>>(std::istream& is, Bingo_board& board)
	{
		std::string line;
		for (size_t row = 0; row < 5; ++row)
		{
			std::getline(is, line);
			std::istringstream line_stream(line);
			for (size_t column = 0; column < 5; ++column)
			{
				int number = 0;
				line_stream >> number;
				board.m_squares[row][column] = Square{ number, false };
			}
		}

		return is;
	}

} // aoc