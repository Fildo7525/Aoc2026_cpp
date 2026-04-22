#include <algorithm>
#include <execution>
#include <print>
#include <vector>
#include <fstream>

struct Direction {
	int dy;
	int dx;

	bool isValid(const std::vector<std::string> &warehouse)
	{
		return dy >= 0 && dx >= 0 && dy < warehouse.size() && dx < warehouse[0].size();
	}
};

Direction operator+(const Direction &lhs, const Direction &rhs)
{
	return Direction{lhs.dy + rhs.dy, lhs.dx + rhs.dx};
}

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::vector<std::string> warehouse;
	std::string line;

	std::vector<Direction> dirs {
		Direction{-1, 0}, // UP
		Direction{-1, 1}, // UP_RIGHT
		Direction{ 0, 1}, // RIGHT
		Direction{ 1, 1}, // DOWN_RIGHT
		Direction{ 1, 0}, // DOWN
		Direction{ 1,-1}, // DOWN_LEFT
		Direction{ 0,-1}, // LEFT
		Direction{-1,-1}, // UP_LEFT

	};

	while (std::getline(input, line)) {
		warehouse.push_back(line);
		std::println("{}", line);
	}
	std::println("");

	unsigned int canBeRemoved = 0;
	bool somethingIsRemoved = true;
	while (somethingIsRemoved) {
		somethingIsRemoved = false;
		std::vector<Direction> toBeRemoved;

		for (int y = 0; y < warehouse.size(); y++) {
			for (int x = 0; x < warehouse[y].size(); x++) {
				auto pos = Direction{y, x};

				if (warehouse[pos.dy][pos.dx] == '.')
					continue;

				int numberOfSurroundingRolls = 0;
				for (const auto &dir : dirs) {
					auto newPos = pos + dir;
					if (!newPos.isValid(warehouse))
						continue;

					if (warehouse[newPos.dy][newPos.dx] == '@')
						numberOfSurroundingRolls++;
				}

				if (numberOfSurroundingRolls < 4) {
					toBeRemoved.push_back(pos);
				}
			}
		}

		if (toBeRemoved.size() != 0) {
			somethingIsRemoved = true;
			canBeRemoved += toBeRemoved.size();
		}

		std::for_each(
			std::execution::par,
			toBeRemoved.begin(),
			toBeRemoved.end(),
			[&warehouse] (const Direction &d) { warehouse[d.dy][d.dx] = '.'; }
		);
	}

	for (const auto &line : warehouse) {
		std::println("{}", line);
	}

	std::println("");

	std::println("We can remove {} rolls of paper", canBeRemoved);

	return 0;
}

