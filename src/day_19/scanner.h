#ifndef AOC_2021_DAY_19_SCANNER_H
#define AOC_2021_DAY_19_SCANNER_H

#include "utility//point.h"

#include <vector>
#include <unordered_set>

namespace aoc
{
	class Scanner
	{
	public:
		Scanner();

		void rotate_axis();
		void change_axis();
		void align();
		bool match(const std::unordered_set<Vec>& other);

		std::vector<Vec> beacons;
		int axis;
		Vec pos;
	};

} // aoc

#endif // !AOC_2021_DAY_19_SCANNER_H
