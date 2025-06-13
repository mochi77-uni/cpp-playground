
#include <iostream>
#include <string>

std::string f() {
	return "hello world";
}

int main() {
	std::string_view sv = f();
	std::cout << sv << std::endl;
	return 0;
}