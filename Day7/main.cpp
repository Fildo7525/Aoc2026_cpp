#include "Day7.h"
#include <algorithm>
#include <cmath>
#include <deque>
#include <ranges>
#include <set>
#include <print>


constexpr char SPLITTER = '^';

struct Point
{
	size_t y;
	size_t x;

	Point &down()
	{
		this->y++;
		return *this;
	}

	std::tuple<Point, Point> split()
	{
		this->y--;

		Point left = *this;
		left.x--;

		Point right = *this;
		right.x++;

		return {left, right};
	}

};

bool operator<(const Point &lhs, const Point &rhs) {
	// return std::powf(lhs.x*lhs.x + lhs.y*lhs.y, 0.5) < std::powf(lhs.x*lhs.x + lhs.y*lhs.y, 0.5);
	return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator==(const Point &lhs, const Point &rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <>
struct std::formatter<Point> {
    // No custom format options for now
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Point& p, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "(y: {}, x: {})", p.y, p.x);
    }
};


int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;
	std::vector<std::string> space;

	while (std::getline(input, line)) {
		space.push_back(line);
	}

	auto start = Point{ .y = 0, .x = space[0].find('S') };

	std::set<Point> rays{start};

	// std::println("Start position = {}", start);
	std::ranges::for_each(space, [](const std::string &s) { std::println("{}", s); });
	int splits = 0;

	while(!rays.empty()) {
		auto ray = *rays.begin();
		rays.erase(rays.begin());

		ray.down();

		if (ray.y == space.size() || space[ray.y][ray.x] == '|') {
			continue;
		}

		// std::println("Tracking ray at position {}", ray);
		// std::println("all rays ({}): {}", rays.size(), rays);

		if (space[ray.y][ray.x] == SPLITTER) {
			auto [l, r] = ray.split();
			// std::println("{} Splitting ray on {} into {} and {}", splits+1, ray, l, r);
			rays.insert(l);
			rays.insert(r);
			splits++;
		}
		else {
			rays.insert(ray);
			space[ray.y][ray.x] = '|';
		}

		// std::ranges::for_each(space, [](const std::string &s) { std::println("{}", s); });
		// std::println("");
	}


	std::println("Counted {} splits", splits);

	return 0;
}

