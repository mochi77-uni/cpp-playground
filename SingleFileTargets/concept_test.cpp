
#include <iostream>

template<typename T>
	requires std::convertible_to<T, int>
int castToInt(T val) {
	return static_cast<int>(val);
}

template<typename T> concept C = std::is_pointer_v<T>;
template<typename T> requires C<T>
bool nullCheck(T ptr) {
	return ptr != nullptr;
}

template<typename T>
concept has_first = requires(T t) {
	t.first;
};
template<has_first T>
auto getFirst(const T& val) {
	return val.first;
}

struct MyStruct {
	int first;
};

int main() {
	castToInt(5);
	castToInt(5.5);
	castToInt(true);
	// castToInt("string");

	int a = 5;
	nullCheck(&a);
	nullCheck("test");

	getFirst(std::make_pair(5, "abc"));
	getFirst(MyStruct{6});

	return 0;
}