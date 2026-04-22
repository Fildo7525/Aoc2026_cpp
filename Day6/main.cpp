#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <print>
#include <vector>

using ull = unsigned long long;
std::vector<std::string> split(const std::string &str, const char delimiter);

struct Calculation {
	std::vector<ull> numbers;
	char operation;

	ull execute() const
	{
		if (operation == '+'){
			return std::accumulate(numbers.begin(), numbers.end(), 0ull);
		}
		else if (operation == '*') {
			return std::accumulate(numbers.begin(), numbers.end(), 1ull, std::multiplies<>());
		}
		return -1;
	}
};

template <>
struct std::formatter<Calculation> {
    // No custom format options for now
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Calculation& p, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.numbers, p.operation);
    }
};

void pt1()
{
	std::fstream input("../input", std::ios::in);
	std::string line;
	std::vector<Calculation> calcs;

	int i = 0;
	while (std::getline(input, line)) {
		try {
			auto l = split(line, ' ') |
				std::views::filter([] (const std::string &s) { return !s.empty(); }) |
				std::views::transform([](const std::string &s) { std::println("Converting: {}", s); return std::stoi(s); }) |
				std::ranges::to<std::vector>();

			if (i == 0)
				calcs.resize(l.size());

			for (size_t j = 0; j < calcs.size(); j++) {
				calcs[j].numbers.push_back(l[j]);
			}
			i++;
		}
		catch (std::exception e) {
			auto l = split(line, ' ') | std::views::filter([] (const std::string &s) { return !s.empty(); }) | std::ranges::to<std::vector>();
			std::println("Handling error on vector: {}", l);

			for (size_t j = 0; j < l.size(); j++) {
				calcs[j].operation = l[j][0];
			}
		}
	}

	unsigned long long sum = 0;
	// std::ranges::for_each(calcs, [&sum](const Calculation &c) { std::println("{} returns: {}", c, c.execute()); sum += c.execute(); });

	std::println("Sum is {}", sum);
}

int main(int argc, char *argv[])
{
	std::fstream input("../input", std::ios::in);
	std::string line;
	std::vector<Calculation> calcs;
	std::vector<std::string> tmp_lines;

	int i = 0;
	while (std::getline(input, line)) {
		tmp_lines.push_back(line);
	}

	auto start = tmp_lines.back().begin();
	auto numsStart = 0;

	while (true) {
		auto endIt = std::find_if(start + 1, tmp_lines.back().end(), [](const char &c) { return c != ' '; });
		char operation = *start;

		std::println("Operator at the end: {}", *endIt);
		auto blockSize = std::distance(start, endIt) - 1;
		start = endIt;

		if (endIt == tmp_lines.back().end())
			blockSize++;

		std::println("Block size: {}", blockSize);
		Calculation c{.operation = operation};
		std::ranges::fill_n(std::back_inserter(c.numbers), blockSize, 0);

		for (size_t j = 0; j < tmp_lines.size()-1; j++) {
			for (size_t i = numsStart; i < numsStart + blockSize; i++) {
				if (tmp_lines[j][i] != ' ') {
					c.numbers[i - numsStart] = c.numbers[i - numsStart] * 10 + tmp_lines[j][i] - '0';
				}
			}
		}

		numsStart += blockSize + 1;
		std::println("Moving the block start to: {}", numsStart);

		std::println("nums in c: {}", c);
		calcs.push_back(std::move(c));

		if (endIt == tmp_lines.back().end()) {
			break;
		}

	}

	std::ranges::for_each(calcs, [](const Calculation &c) { std::println("{}", c); });

	unsigned long long sum = 0;
	std::ranges::for_each(calcs, [&sum](const Calculation &c) { auto e = c.execute(); std::println("{} returns: {}", c, e); sum += e; });

	std::println("Sum is {}", sum);

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
