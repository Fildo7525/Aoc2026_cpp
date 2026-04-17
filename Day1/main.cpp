#include "Day1.h"
#include <string>
#include <print>

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;

	int dial = 50;
	int zero = 0;
	std::println("The dial start by pointing at {}.", dial);
	std::string info = "";

	while (std::getline(input, line)) {
		int rotation = std::stoi(line.substr(1));
		if (line[0] == 'L') {
			rotation *= -1;
		}

		int oldDial = dial;
		dial += rotation;

		if (dial != 0) {
			zero += std::abs(dial / 100);
			if (dial % 100 == 0) {
				zero -= 1;
			}
			if (dial / 100 != 0) {
				info = std::format("During this rotation the dial points to zero {} times", dial / 100);
			}
			else {
				info = "";
			}

			zero += (oldDial*dial < 0 ? 1 : 0);
			if (oldDial*dial < 0 ? 1 : 0) {
				info += " And once passed the boundry";
			}
		}

		dial = dial % 100;

		if (dial < 0) {
			dial += 100;
		}

		zero += (dial == 0 ? 1 : 0);

		std::println("The dial is rotated {} to point at {}. {}", rotation, dial, info);
	}


	std::println("The dial points at zero {} times", zero);

	return 0;
}

