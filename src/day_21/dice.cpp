#include "day_21/dice.h"

#include <iostream>

namespace aoc
{
	Dice::Dice() :
		m_value(1),
		m_max(100),
		m_rolls(0)
	{

	}

	Dice::Dice(int max) :
		m_value(1),
		m_max(max),
		m_rolls(0)
	{

	}

	Dice::Dice(int start, int max) :
		m_value(start),
		m_max(max),
		m_rolls(0)
	{

	}

	int Dice::roll()
	{
		++m_rolls;
		int prev = m_value++;
		m_value = ((m_value - 1) % m_max) + 1;
		return prev;
	}

	int Dice::roll_three()
	{
		int result = 0;
		for (size_t i = 0; i < 3; ++i)
		{
			result += roll();
		}

		return result;
	}

	int Dice::current() const
	{
		return m_value;
	}

	int Dice::total_rolls() const
	{
		return m_rolls;
	}

} // aoc