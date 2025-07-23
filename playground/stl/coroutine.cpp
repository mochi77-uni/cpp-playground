
#include <coroutine>
#include <generator>
#include <iostream>
#include <ranges>

std::generator<std::pair<int, int>> fib_generator() {
	int current = 0;
	int next = 1;

	int index = 0;
	while (true) {
		co_yield {index++, current};
		std::tie(current, next) = std::make_pair(next, current + next);
	}
}

int main() {
	using namespace std::views;

	for (auto [index, value] : fib_generator() | take(15)) {
		std::print(std::cout, "{0}: {1}\n", index, value);
	}

	return 0;
}