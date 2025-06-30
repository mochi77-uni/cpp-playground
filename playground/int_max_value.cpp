
#include <iomanip>
#include <iostream>
#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

template<typename T, typename ... U>
concept either = (std::same_as<T, U> || ...);

#ifdef __GNUC__
template<typename T>
	requires either<T, __int128_t, __uint128_t>
std::ostream& operator<<(std::ostream& stream, T value) {
	std::ostream::sentry sentry(stream);
	if (!sentry) return stream;

	T temp = value < 0 ? -value : value;
	char buffer[128] = {};
	char* d = std::end(buffer);
	do {
		--d;
		*d = "0123456789"[temp % 10];
		temp /= 10;
	} while (temp != 0);

	if (value < 0) *--d = '-';
	const int length = std::end(buffer) - d;
	return stream << std::string_view(d, length);
}
#endif

int main() {
	std::ios::sync_with_stdio(false);

	std::cout << "Cpp Standard\n";
	std::cout << std::setw(15) << "int8_t "   << std::setw(40) << +std::numeric_limits<int8_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint8_t "  << std::setw(40) << +std::numeric_limits<uint8_t>::max() << std::endl;
	std::cout << std::setw(15) << "int16_t "  << std::setw(40) << std::numeric_limits<int16_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint16_t " << std::setw(40) << std::numeric_limits<uint16_t>::max() << std::endl;
	std::cout << std::setw(15) << "int32_t "  << std::setw(40) << std::numeric_limits<int32_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint32_t " << std::setw(40) << std::numeric_limits<uint32_t>::max() << std::endl;
	std::cout << std::setw(15) << "int64_t "  << std::setw(40) << std::numeric_limits<int64_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint64_t " << std::setw(40) << std::numeric_limits<uint64_t>::max() << std::endl;

#ifdef __GNUC__
	std::cout << "GNU Provided\n";
	std::cout << std::setw(15) << "__int128_t "  << std::setw(40) << std::numeric_limits<__int128_t>::max() << std::endl;
	std::cout << std::setw(15) << "__uint128_t " << std::setw(40) << std::numeric_limits<__uint128_t>::max() << std::endl;
#endif

	using namespace boost::multiprecision;
	std::cout << "Boost Provided\n";
	std::cout << std::setw(15) << "int128_t "   << std::setw(40) << std::numeric_limits<int128_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint128_t "  << std::setw(40) << std::numeric_limits<uint128_t>::max() << std::endl;
	std::cout << std::setw(15) << "int256_t "   << std::setw(40) << std::numeric_limits<int256_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint256_t "  << std::setw(40) << std::numeric_limits<uint256_t>::max() << std::endl;
	std::cout << std::setw(15) << "int512_t "   << std::setw(40) << std::numeric_limits<int512_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint512_t "  << std::setw(40) << std::numeric_limits<uint512_t>::max() << std::endl;
	std::cout << std::setw(15) << "int1024_t "  << std::setw(40) << std::numeric_limits<int1024_t>::max() << std::endl;
	std::cout << std::setw(15) << "uint1024_t " << std::setw(40) << std::numeric_limits<uint1024_t>::max() << std::endl;

	return 0;
}