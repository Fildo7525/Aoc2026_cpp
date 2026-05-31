#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <map>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <vector>

#define MERGING_ITERATIONS 1000
#define INPUT "../input"

struct Point3d
{
	int64_t x;
	int64_t y;
	int64_t z;
};

bool operator==(const Point3d &p1, const Point3d &p2)
{
	return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

// Lexicographic order — correct for use as std::map key
bool operator<(const Point3d &p1, const Point3d &p2)
{
	if (p1.x != p2.x) return p1.x < p2.x;
	if (p1.y != p2.y) return p1.y < p2.y;
	return p1.z < p2.z;
}

template <>
struct std::formatter<Point3d> {
	constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
	template <typename FormatContext>
	auto format(const Point3d &p, FormatContext &ctx) const {
		return std::format_to(ctx.out(), "({:7},{:7},{:7})", p.x, p.y, p.z);
	}
};

// Squared distance — integer, no floating point needed
int64_t sqDist(const Point3d &a, const Point3d &b)
{
	int64_t dx = b.x - a.x;
	int64_t dy = b.y - a.y;
	int64_t dz = b.z - a.z;
	return dx*dx + dy*dy + dz*dz;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
	std::vector<std::string> out;
	auto start = str.begin();
	while (true) {
		auto found = std::find(start, str.end(), delimiter);
		out.push_back(str.substr(start - str.begin(), found - start));
		if (found == str.end()) break;
		start = found + 1;
	}
	return out;
}

int main()
{
	std::fstream input(INPUT, std::ios::in);
	std::string line;
	std::vector<Point3d> junctionBoxes;

	while (std::getline(input, line)) {
		auto parts = split(line, ',');
		junctionBoxes.push_back(Point3d{
			.x = std::stol(parts[0]),
			.y = std::stol(parts[1]),
			.z = std::stol(parts[2])
		});
	}

	const size_t n = junctionBoxes.size();
	std::println("Loaded {} junction boxes.", n);

	// Collect ALL unique pairs (i < j) — no duplicates, no floating point
	using Edge = std::tuple<int64_t, size_t, size_t>;
	std::vector<Edge> edges;
	edges.reserve(n * (n - 1) / 2);

	for (size_t i = 0; i < n; i++)
		for (size_t j = i + 1; j < n; j++)
			edges.emplace_back(sqDist(junctionBoxes[i], junctionBoxes[j]), i, j);

	// Sort by distance ascending
	std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return std::get<0>(a) < std::get<0>(b);
	});

	std::println("Total unique pairs: {}", edges.size());

	// Union-Find over indices
	std::vector<int> circuits(n);
	std::iota(circuits.begin(), circuits.end(), 0);

	std::function<int(int)> find = [&](int x) -> int {
		while (circuits[x] != x) {
			circuits[x] = circuits[circuits[x]];
			x = circuits[x];
		}
		return x;
	};

	auto unite = [&](size_t a, size_t b) {
		int realA = find(a);
		int realB = find(b);
		if (realA != realB) circuits[realB] = realA;
	};

	// Process the MERGING_ITERATIONS closest pairs
	for (size_t k = 0; k < MERGING_ITERATIONS && k < edges.size(); k++) {
		auto [dist, i, j] = edges[k];
		unite(i, j);
	}

	// Count members per circuit
	std::map<int, int> groupCounts;
	for (size_t i = 0; i < n; i++)
		groupCounts[find(i)]++;

	// Sort groups by size descending
	std::vector<int> sizes;
	sizes.reserve(groupCounts.size());
	for (const auto &[id, count] : groupCounts)
		sizes.push_back(count);
	std::ranges::sort(sizes, std::greater<>{});

	std::println("Number of circuits: {}", sizes.size());
	std::println("Top 5 circuit sizes: {}", sizes | std::views::take(5));

	int64_t product = (int64_t)sizes[0] * sizes[1] * sizes[2];
	std::println("Product of 3 largest circuits ({} * {} * {}): {}",
				 sizes[0], sizes[1], sizes[2], product);

	return 0;
}
