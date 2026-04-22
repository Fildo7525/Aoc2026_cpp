#include "Day5.h"
#include <algorithm>
#include <atomic>
#include <print>
#include <string>
#include <vector>

using ull = unsigned long long;

struct Range{
	ull start;
	ull end;

	bool inRange(ull num) const
	{
		return start <= num && num <= end;
	}

	ull size() const
	{
		return (end - start) + 1;
	}
};

bool operator==(const Range &lhs, const Range &rhs)
{
	return lhs.start == rhs.start && lhs.end == rhs.end;
}

template <>
struct std::formatter<Range> {
    // No custom format options for now
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Range& p, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.start, p.end);
    }
};

std::vector<std::string> split(const std::string &str, const char delimiter);

void pt1() {
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
}

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;

	std::vector<Range> freshRanges;
	std::vector<ull> toIdentify;

	while (std::getline(input, line)) {
		if (line == "") {
			break;
		}

		auto r = split(line, '-');
		auto rng = Range{.start = std::stoull(r[0]), .end=std::stoull(r[1])};
		freshRanges.push_back(rng);
	}

	std::ranges::sort(freshRanges, [](const Range &lhs, const Range &rhs) { return lhs.start < rhs.start; });

	std::println("\nAfter sort");
	std::ranges::for_each(freshRanges, [](const Range &r) {std::println("{}", r);});

	for (size_t i = 0; i < freshRanges.size()-1; ) {
		if (freshRanges[i].end >= freshRanges[i+1].end) {
			freshRanges.erase(freshRanges.begin() + i+1);
		}
		else if (freshRanges[i].end >= freshRanges[i+1].start-1) {
			freshRanges[i].end = freshRanges[i+1].end;
			freshRanges.erase(freshRanges.begin() + i+1);
		}
		else {
			i++;
		}
	}

	std::println("\nAfter removal");
	std::ranges::for_each(freshRanges, [](const Range &r) {std::println("{}", r);});

	ull freshItems = 0;
	std::ranges::for_each(
		freshRanges,
		[&freshItems](const Range &r) {
			freshItems += r.size();
		});
	std::println("Number of fresh items in total: {}", freshItems);

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

// RE: 357 608 232 770 687
// GT: 357 608 232 770 687
// Range (525730578983777, 531697056572126) has 5966477588350 items
