#include "day_19/scanner.h"

#include "utility/point.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <optional>

namespace aoc
{
	Scanner::Scanner() :
		m_axis(0),
		m_pos(Vec::origin)
	{

	}

	void Scanner::add_beacon(const Vec& beacon)
	{
		m_beacons.push_back(beacon);
	}

	const std::vector<Vec>& Scanner::beacons() const
	{
		return m_beacons;
	}

	std::vector<Vec>& Scanner::beacons()
	{
		return m_beacons;
	}

	const Vec& Scanner::position() const
	{
		return m_pos;
	}

	Vec& Scanner::position()
	{
		return m_pos;
	}

	void Scanner::rotate()
	{
		for (auto& beacon : m_beacons)
		{
			beacon = { -beacon.y ,beacon.x ,beacon.z };
		}
	}

	void Scanner::rotate_axis()
	{
		for (auto& beacon : m_beacons)
		{
			switch (m_axis)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				beacon = { beacon.z, beacon.y, -beacon.x };
				break;
			case 4:
				beacon = { beacon.x, -beacon.z, beacon.y };
				break;
			case 5:
				beacon = { beacon.x, -beacon.y, -beacon.z };
				break;
			default:
				break;
			}
		}

		++m_axis;
	}

	void Scanner::reset()
	{
		m_axis = 0;
	}

	bool Scanner::try_match(const std::unordered_set<Vec>& other)
	{
		std::optional<Vec> direction = matching_direction(other);
		if (!direction)
		{
			return false;
		}

		m_pos = direction.value();
		for (auto& beacon : m_beacons)
		{
			beacon -= m_pos;
		}

		return true;
	}

	std::optional<Vec> Scanner::matching_direction(const std::unordered_set<Vec>& other)
	{
		std::unordered_map<Vec, int> distances;
		for (const auto& beacons_1 : other)
		{
			for (const auto& beacons_2 : m_beacons)
			{
				Vec direction = beacons_2 - beacons_1;
				if (++distances[direction] == 4)
				{
					return direction;
				}
			}
		}

		return std::nullopt;
	}

} // aoc