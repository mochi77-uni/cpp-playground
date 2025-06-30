
#include <iostream>
#include <format>
#include <cstring>

int main() {
	constexpr char shader[] = {
		#embed "shader.vert" \
			suffix(,)
		0
	};

	std::println(std::cout, "Contents:");
	std::cout << shader << std::endl;
	const auto length = std::strlen(shader);
	std::println(std::cout, "Length: {}", length);
	constexpr auto capacity = std::size(shader);
	std::println(std::cout, "Capacity: {}", capacity);
	std::println(std::cout, "shader[{}]: {}", capacity - 1, static_cast<int>(shader[capacity - 1]));

	return 0;
}