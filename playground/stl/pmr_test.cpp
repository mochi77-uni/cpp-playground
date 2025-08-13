
#include <iostream>
#include <print>
#include <memory_resource>

void print_buffer(const std::span<char>& buffer) {
	size_t counter = 0;

	for (const auto& ch : buffer) {
		constexpr size_t byte_per_line = 16;
		std::string out;

		if (ch == 0) {
			out = "NIL";
		} else if (isalnum(ch)) {
			out.assign(1, ch);
		} else {
			out = std::format("{:2X}", static_cast<uint8_t>(ch));
		}

		std::print("[{:>3}]{:c}", out,
			counter++ < byte_per_line - 1 ? ' ' : '\n');
		if (counter == byte_per_line) counter = 0;
	}
}

int main() {
	constexpr size_t max_buffer_size = 1024;
	alignas(std::max_align_t) char buffer[max_buffer_size]{};

	std::pmr::monotonic_buffer_resource arena{buffer, max_buffer_size};
	std::pmr::vector<std::pmr::string> strings{&arena};

	// objects are created in buffer
	strings.emplace_back("hello");
	strings.emplace_back("pmr");
	strings.emplace_back("world");
	strings.erase(strings.begin());

	for (const auto& s : strings)
		std::println(R"("{}" ({}))", s, s.size());

	std::cout << "[buffer]\n";
	print_buffer({buffer, max_buffer_size});

	return 0;
}