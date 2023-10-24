#include "Apple.h"
#include <algorithm>

void Apple::ChangePos(const std::vector<Snake*>& snake)
{
	srand(time(NULL));

	while (true)
	{
		position.x = 150 + rand() % 200;
		position.y = 150 + rand() % 200;

		UpdateAABB();

		std::vector<bool> col;
		for (auto i : snake)
		{
			col.push_back(CheckCollision(*i));
		}

		if (std::any_of(begin(col), end(col), [](bool intersect) {
			return intersect == true;
			})) {
			std::cout << "intersect" << std::endl;
			std::cout << "At point: (" << position.x << ";" << position.y << ")" << std::endl;
		}

		if (std::none_of(col.begin(), col.end(), [](bool intersect) {
			return intersect == true;
		})) break;	                                                       // if at least one element is true then restart
	}
}
