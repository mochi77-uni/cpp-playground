
#include <numbers>
#include <iostream>
#include <iomanip>

template<typename T>
consteval T require_consteval(T val) {
	return val;
}

int main() {
	namespace sn = std::numbers;

	/* use consteval dummy function to demonstrate std::numbers constant
	 * are compile time evaluated */
	std::cout << std::setprecision(std::numeric_limits<decltype(sn::pi)>::max_digits10 - 1);
	std::cout << require_consteval(sn::pi) << '\n';
	std::cout << std::setprecision(std::numeric_limits<decltype(sn::e)>::max_digits10 - 1);
	std::cout << require_consteval(sn::e) << '\n';

	std::cout << "double:\n";
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10 - 1);
	std::cout << require_consteval(sn::pi_v<double>) << '\n';
	std::cout << require_consteval(sn::e_v<double>) << '\n';

	std::cout << "long double:\n";
	std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10 - 1);
	std::cout << require_consteval(sn::pi_v<long double>) << '\n';
	std::cout << require_consteval(sn::e_v<long double>) << '\n';

	return 0;
}