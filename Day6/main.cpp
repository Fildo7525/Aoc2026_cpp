#include "Day6.h"
#include <functional>
#include <numeric>
#include <ranges>
#include <print>

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

int main(int argc, char *argv[])
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
	std::ranges::for_each(calcs, [&sum](const Calculation &c) { std::println("{} returns: {}", c, c.execute()); sum += c.execute(); });

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
