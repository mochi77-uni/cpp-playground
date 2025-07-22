
#include <print>
#include <unordered_map>
#include <vector>

int main() {
	constexpr auto str = std::string_view{"hello world"};

	// store each bit of string in vector<bool>
	std::vector<bool> bitStorage{};
	for (const auto& ch : str) {
		for (uint8_t mask = 0b10000000; mask > 0; mask >>= 1) {
			bitStorage.emplace_back(ch & mask);
		}
	}

	// create base64 map
	std::unordered_map<uint8_t, char> map{};
	uint8_t counter{0};
	for (char ch = 'A'; ch <= 'Z'; ++ch) map.insert({counter++, ch});
	for (char ch = 'a'; ch <= 'z'; ++ch) map.insert({counter++, ch});
	for (char ch = '0'; ch <= '9'; ++ch) map.insert({counter++, ch});
	map.insert({counter++, '+'});
	map.insert({counter++, '/'});

	// encode input string
	constexpr size_t keyBitLength = 6;
	std::string outString;
	const size_t remainder = bitStorage.size() % keyBitLength;
	for (size_t i = 0; i < keyBitLength - remainder; ++i)
		bitStorage.emplace_back(false);
	for (size_t i = 0; i < bitStorage.size(); i += keyBitLength) {
		uint8_t outBits{};
		outBits = bitStorage[i];
		for (size_t j = i + 1; j < i + keyBitLength; ++j)
			outBits = (outBits << 1) | bitStorage[j] & 1;
		std::print("{:08b} ", outBits);
		std::println("{}", map.at(outBits));
		outString += map.at(outBits);
	}
	for (size_t i = 0; i < keyBitLength - remainder; ++i)
		outString += '=';

	std::println("Original: {}", str);
	std::println("Encoded:  {}", outString);

	return 0;
}