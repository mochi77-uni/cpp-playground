
#include <cmath>
#include <print>
#include <expected>
#include <iomanip>

enum class ParseError {
	InvalidInput,
	Overflow
};

auto ParseNumber(std::string_view& s) -> std::expected<double, ParseError> {
	const char* begin = s.data();
	char* end = nullptr;
	double retval = std::strtod(begin, &end);

	if (begin == end)
		return std::unexpected(ParseError::InvalidInput);
	if (std::isinf(retval))
		return std::unexpected(ParseError::Overflow);

	s.remove_prefix(end - begin);
	return retval;
}

int main() {
	auto process = [](std::string_view s) {
		std::print(R"(str: "{}", )", s);
		if (const auto num = ParseNumber(s); num.has_value())
			std::println("value: {}", *num);
		else if (num.error() == ParseError::InvalidInput)
			std::println("error: invalid input");
		else if (num.error() == ParseError::Overflow)
			std::println("error: overflow");
		else
			std::println("unexpected");
	};

	for (const auto src : {"42", "42aaa", "meow", "inf"})
		process(src);

	return 0;
}