#include "Day5.h"
#include <algorithm>
#include <atomic>
#include <print>
#include <string>

using ull = unsigned long long;

struct Range{
	ull start;
	ull end;

	bool inRange(ull num) const
	{
		return start <= num && num <= end;
	}
};

std::vector<std::string> split(const std::string &str, const char delimiter);

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;

	std::vector<Range> freshRanges;
	std::vector<ull> toIdentify;

	bool loadedAllRanges = false;
	while (std::getline(input, line)) {
		// std::println("Line: '{}'", line);

		if (line == "") {
			loadedAllRanges = true;
			continue;
		}

		if (!loadedAllRanges) {
			auto r = split(line, '-');
			auto rng = Range{.start = std::stoull(r[0]), .end=std::stoull(r[1])};
			freshRanges.push_back(rng);
		}
		else {
			toIdentify.push_back(std::stoull(line));
		}
	}

	ull freshCount = 0;
	for (const auto &ingredient : toIdentify) {
		for (const auto &r : freshRanges) {
			if (r.inRange(ingredient)) {
				freshCount++;
				std::println("Fresh ingredient: {}", ingredient);
				break;
			}
		}
	}

	std::println("Fresh number of ingredients: {}", freshCount);

	return 0;
}

std::vector<std::string> split(const std::string &str, const char delimiter)
{
	std::vector<std::string> out;
	auto start = str.begin();
	while (true) {
		auto found = std::find(start, str.end(), delimiter);
		if (found == str.end()) {
			out.push_back(str.substr(start-str.begin()));
			break;
		}

		out.push_back(str.substr(start - str.begin(), found - start));
		start = found+1;
	}

	return out;
}
