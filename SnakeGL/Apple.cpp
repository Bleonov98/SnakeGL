#include "Apple.h"
#include <algorithm>

void Apple::ChangePos(const std::vector<Snake*>& snake)
{
	srand(time(NULL));

	while (true)
	{
		position.x = 130 + rand() % 900;
		position.y = 100 + rand() % 610;

		UpdateAABB();

		std::vector<bool> col;
		for (auto &i : snake)
		{
			col.push_back(CheckCollision(*i) || FieldCollision());
		}

		if (std::none_of(col.begin(), col.end(), [](bool intersect) {
			return intersect == true;
		})) break;	                                                       // if at least one element is true then restart
	}
}
