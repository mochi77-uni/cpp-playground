
#include <iostream>
#include <format>

template<typename T>
concept formattable = requires(T t, std::format_context ctx) {
	std::formatter<T>::format(t, ctx);
};

template<typename T>
struct is_formattable {
	static constexpr bool value = formattable<T>;
};

template<typename T>
inline constexpr bool is_formattable_v = is_formattable<T>::value;

struct Point {
	int x, y;
};

// general template specialization syntax
template<>	// full specialization
struct std::formatter<Point> : std::formatter<std::string> {
	constexpr static auto format(const Point& p, std::format_context& ctx) {
		return format_to(ctx.out(), "({}, {})", p.x, p.y);
	}
};

template<typename T>
std::string make_string(const T& t) {
	using namespace std::literals;

	if constexpr (is_formattable_v<T>) {
		return std::format("Formattable({})", t);
	} else if constexpr (std::is_pointer_v<T>) {
		return std::format("Pointer({})", static_cast<void *>(t));
	} else if constexpr (std::is_same_v<T, bool>) {
		return std::format("Bool({})", t ? "true" : "false");
	} else if constexpr (std::is_same_v<T, char>) {
		return std::format("Char('{}')", t);
	} else if constexpr (std::is_convertible_v<T, std::string_view>) {
		return std::format(R"(String("{}"))", std::string_view(t));
	}else if constexpr (std::is_integral_v<T>) {
		return std::format("Integral({})", std::to_string(t));
	} else if constexpr (std::is_floating_point_v<T>) {
		return std::format("Float({})", std::to_string(t));
	} else {
		return "Unknown(null)";
	}
}

int main() {
	using namespace std::literals;

	int value = 5;

	std::cout << make_string(value) << '\n';
	std::cout << make_string(5.5) << '\n';
	std::cout << make_string("5.5") << '\n';
	std::cout << make_string('5') << '\n';
	std::cout << make_string(true) << '\n';
	std::cout << make_string(&value) << '\n';
	std::cout << make_string(Point{2, 4}) << '\n';

	return 0;
}