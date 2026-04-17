#include "Day1.h"
#include <cstdint>
#include <string>
#include <vector>
#include <print>

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;

	int dial = 50;
	int zero = 0;
	std::println("The dial start by pointing at {}", dial);

	while (std::getline(input, line)) {
		int rotation = std::stoi(line.substr(1));
		if (line[0] == 'L') {
			rotation *= -1;
		}

		dial += rotation;

		if (dial < 0) {
			dial += 100;
		}

		dial = dial % 100;
		zero += (dial == 0 ? 1 : 0);
		std::println("The dial is rotated {} to point at {}", rotation, dial);
	}


	std::println("The dial points at zero {} times", zero);

	return 0;
}

