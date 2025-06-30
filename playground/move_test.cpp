
#include <iostream>
#include <vector>
#include <sstream>

class MyClass {
public:
	int d;
	float f;
	char c;

	MyClass() = delete;
	MyClass(int d, float f, char c)
		: d(d), f(f), c(c) {}

	MyClass(MyClass&& other) noexcept
		: d(other.d), f(other.f), c(other.c) {
		other.d = 0;
		other.f = 0.f;
		other.c = '\0';
	}

	std::string to_str() const {
		return std::format("{} {} {}", d, f, c);
	}
};

int main() {
	std::vector<int> vec = {1, 2, 3};
	std::print(std::cout, "&vec = {}\n", static_cast<const void*>(vec.data()));
	std::vector<int> vec2 = std::move(vec);
	std::print(std::cout, "&vec = {}\n", static_cast<const void*>(vec.data()));
	std::print(std::cout, "&vec2 = {}\n", static_cast<const void*>(vec2.data()));

	MyClass obj(3, 4.5, 'c');
	std::print(std::cout, "obj = {}\n", obj.to_str());
	MyClass obj2 = std::move(obj);
	std::print(std::cout, "obj = {}\n", obj.to_str());
	std::print(std::cout, "obj2 = {}\n", obj2.to_str());
	return 0;
}