
#include <iostream>

class MyClass {
	int bigUnit;
	int smallUnit;
public:
	MyClass(const int _bigUnit, const int _smallUnit) : bigUnit(_bigUnit), smallUnit(_smallUnit) {}

	constexpr bool operator==(const MyClass& other) const {
		return bigUnit == other.bigUnit;
	}

	constexpr std::strong_ordering operator<=>(const MyClass& other) const {
		auto ret = std::compare_three_way{}(this->bigUnit, other.bigUnit);
		if (ret == std::strong_ordering::equal)
			ret = std::compare_three_way{}(this->smallUnit, other.smallUnit);
		return ret;
	}
};

int main() {
	const MyClass myClass(3, 4);
	const MyClass myClass2(3, 5);

	if (auto result = std::compare_three_way{}(myClass, myClass2);
			 result == std::strong_ordering::less)
		std::cout << "less" << std::endl;
	else if (result == std::strong_ordering::greater)
		std::cout << "greater" << std::endl;
	else
		std::cout << "equal" << std::endl;
	return 0;
}