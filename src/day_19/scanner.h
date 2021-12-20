#ifndef AOC_2021_DAY_19_SCANNER_H
#define AOC_2021_DAY_19_SCANNER_H

#include "utility/point.h"

#include <vector>
#include <unordered_set>
#include <optional>

namespace aoc
{
	class Scanner
	{
	public:
		Scanner();
		
		void add_beacon(const Vec& beacon);
		const std::vector<Vec>& beacons() const;
		std::vector<Vec>& beacons();
		const Vec& position() const;
		Vec& position();

		void rotate_axis();
		void rotate();
		bool try_match(const std::unordered_set<Vec>& other);
		void reset();
		
	private:
		std::optional<Vec> matching_direction(const std::unordered_set<Vec>& other);

		std::vector<Vec> m_beacons;
		Vec m_pos;
		int m_axis;
	};

} // aoc

#endif // !AOC_2021_DAY_19_SCANNER_H
