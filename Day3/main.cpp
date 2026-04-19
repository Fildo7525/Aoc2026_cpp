#include "Day3.h"
#include <algorithm>
#include <print>
#include <cstdint>
#include <cstdio>
#include <ranges>

constexpr int MAX_BATTERIES = 12;

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;
	unsigned long long sum = 0;

	while (std::getline(input, line)) {
		std::vector<uint8_t> batteries;
		batteries.reserve(line.size());
		std::ranges::for_each(line, [&batteries](const char c) { batteries.push_back(c - '0'); });

		std::vector<uint8_t>::iterator first = batteries.begin();

		unsigned long long mid = 0;
		for (int i = MAX_BATTERIES-1; i >= 0; i--) {
			std::ranges::subrange start(first, batteries.end() - i);
			// std::println("range: {}", start);
			first = std::ranges::max_element(start);

			mid = mid * 10 + *first; // + std::ranges::max(end);
			first++;
		}

		// std::println("Highest number: {}", mid);
		std::println();
		sum += mid;
	}

	std::println("Sum: {}", sum);

	return 0;
}

