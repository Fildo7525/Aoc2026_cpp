#include "Day2.h"
#include <algorithm>
#include <print>
#include <string>

using ull = unsigned long long;

struct Range {
	ull start;
	ull end;
};


std::vector<std::string> split(const std::string &str, const char delimiter);
bool isValidID(const std::string &id);

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;

	std::vector<Range> idRanges;

	while (std::getline(input, line)) {
		std::println("Splitting {}", line);
		auto devided = split(line, ',');
		for (auto &r : devided) {
			auto rng = split(r, '-');
			idRanges.push_back(Range{std::stoull(rng[0]), std::stoull(rng[1])});
			std::println("Range[.start={}, .end={}]", idRanges.back().start, idRanges.back().end);
		}
	}

	ull sum = 0;
	for (const auto &r : idRanges) {
		std::println("Chacking range {} - {}", r.start, r.end);
		for (ull i = r.start; i <= r.end; i++) {
			if (!isValidID(std::to_string(i))) {
				sum += i;
				std::println("Invalid number: {}", i);
			}
		}
	}
	std::println("SUM of invalid: {}", sum);

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

bool checkSequence(const std::string &id)
{
	for (size_t i = 1; i <= id.size()/2; i++) {
		if (id.size() % i != 0) {
			continue;
		}

		const auto &a = id.substr(0, i);
		bool isValid = true;

		for (size_t j = 0; j  < id.length()/a.length(); j++) {
			if (a == id.substr(a.length()*j, a.length())) {
				isValid = false;
			}
			else {
				isValid = true;
				break;
			}
		}
		if (not isValid) {
			return false;
		}
	}

	return true;
}

bool isValidID(const std::string &id)
{
	if (id[0] == 0) {
		return false;
	}

	return checkSequence(id);
}

