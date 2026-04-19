#include "Day3.h"
#include <algorithm>
#include <print>
#include <cstdint>
#include <cstdio>
#include <ranges>

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;
	int sum = 0;

	while (std::getline(input, line)) {
		std::vector<uint8_t> batteries;
		batteries.reserve(line.size());
		std::ranges::for_each(line, [&batteries](const char c) { batteries.push_back(c - '0'); });

		std::ranges::subrange start(batteries.begin(), batteries.end() - 1);
		auto first = std::ranges::max_element(start);
		// std::println("first range: {}", start);

		std::ranges::subrange end(first + 1, batteries.end());
		// std::println("second range: {}", end);

		auto mid = *first * 10 + std::ranges::max(end);
		// std::println("Highest {} from range {:}", mid, batteries);
		// std::println();

		sum += mid;
	}

	std::println("Sum: {}", sum);

	return 0;
}

