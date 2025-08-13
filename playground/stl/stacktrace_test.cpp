
#include <iostream>
#include <print>
#include <stacktrace>

int recursive_function(int num, int max_num) {
	if (num < max_num)
		return recursive_function(num + 1, max_num);

	auto st = std::stacktrace::current();
	for (auto begin = st.begin(), end = st.end(), current = begin; current != end; ++current) {
		std::println("[{}] {:s}#{}", current - begin, current->description(), current->source_line());
	}

	return num;
}

int main() {
	std::cout << recursive_function(1, 10) << std::endl;

	return 0;
}