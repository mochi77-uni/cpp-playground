
#include <iostream>
#include <ranges>
#include <vector>

class FibonacciIterator {
	int first, second;
public:
	FibonacciIterator() : first(0), second(1) {}

	friend constexpr bool operator== (const FibonacciIterator& l, const FibonacciIterator& r) noexcept {
		return l.first == r.first && l.second == r.second;
	}

	constexpr int operator*() const noexcept {
		return first;
	}

	constexpr FibonacciIterator& operator++() {
		std::tie(first, second) = std::make_tuple(second, first + second);
		return *this;
	}

	constexpr FibonacciIterator operator++(int) {
		const FibonacciIterator copy = *this;
		std::tie(first, second) = std::make_tuple(second, first + second);
		return copy;
	}

	using value_type = int;
	using difference_type = std::ptrdiff_t;
};
static_assert(std::input_iterator<FibonacciIterator>);

int main() {
	using namespace std::ranges;
	using namespace std::views;

	constexpr auto isDividedByThree = [](const int &val) {
		return val % 3 == 0;
	};

	int count = 0;
	auto markValueWithCount = [&count](const int &val) {
		return std::format("{}:\t{}", ++count, val);
	};

	for (const auto i
		: iota(0) | filter(isDividedByThree) | take(10) | transform(markValueWithCount)) {
		std::cout << i << '\n';
	}

	std::cout << "===============================\n";

	for (const auto i : subrange(FibonacciIterator{}, std::unreachable_sentinel) | take(10)) {
		std::cout << i << '\n';
	}

	return 0;
}