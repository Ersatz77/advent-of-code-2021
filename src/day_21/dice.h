#ifndef AOC_2021_DAY_21_DICE_H
#define AOC_2021_DAY_21_DICE_H

namespace aoc
{
	class Dice
	{
	public:
		Dice();
		explicit Dice(int max);
		explicit Dice(int start, int max);

		int roll();
		int roll_three();
		int current() const;
		int total_rolls() const;

	private:
		int m_value;
		int m_max;
		int m_rolls;
	};

} // aoc

#endif // !AOC_2021_DAY_21_DICE_H
