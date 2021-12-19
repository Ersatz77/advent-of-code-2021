#include "day_19/scanner.h"

#include "utility/point.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace aoc
{
	Scanner::Scanner() :
		axis(0),
		pos(Vec::origin)
	{

	}

	void Scanner::rotate_axis()
	{
		for (auto& beacon : beacons)
		{
			beacon = { -beacon.y ,beacon.x ,beacon.z };
		}
	}

	void Scanner::change_axis()
	{
		for (auto& beacon : beacons)
		{
			switch (axis)
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

		++axis;
	}

	void Scanner::align()
	{
		for (auto& beacon : beacons)
		{
			beacon = beacon - pos;
		}
	}

	bool Scanner::match(const std::unordered_set<Vec>& other)
	{
		std::unordered_map<Vec, int> distances;
		Vec direction;
		for (const auto& beacons_1 : other)
		{
			for (const auto& beacons_2 : beacons)
			{
				direction = beacons_2 - beacons_1;
				if (++distances[direction] == 4)
				{
					pos = direction;
					return true;
				}
			}
		}

		return false;
	}

} // aoc