
#include <iostream>
#include <print>

class SimpleClass {
public:
	std::string name;
	explicit SimpleClass(const std::string_view name) : name(name) {}
};

class CopiableClass {
public:
	std::string name;
	explicit CopiableClass(const std::string_view name) : name(name) {}

	CopiableClass(const CopiableClass& obj) {
		this->name = obj.name;
		std::println(std::cout, "CopiableClass({}): copy constructor called", name);
	}

	CopiableClass& operator=(const CopiableClass& obj) {
		this->name = obj.name;
		std::println(std::cout, "CopiableClass({}): copy assignment called", name);
		return *this;
	}

	// In C++, defining a copy constructor implicitly makes the class move constructible
	// by falling back to copy operations when move operations are not available.
	// Here we explicitly delete the move constructor to prevent this fallback behavior.
	// CopiableClass(CopiableClass &&) = delete;

	// Similarly, defining a copy assignment operator implicitly makes the class move assignable
	// by falling back to copy assignment when the move assignment is not available.
	// Here we explicitly delete the move assignment operator to prevent this fallback behavior.
	// CopiableClass &operator=(CopiableClass &&) = delete;
};

class MovableClass {
public:
	std::string name;
	explicit MovableClass(const std::string_view name) : name(name) {}

	MovableClass(MovableClass&& obj) noexcept : name(std::move(obj.name)) {
		obj.name = "";
		std::println(std::cout, "MovableClass({}): move constructor called", name);
	}

	MovableClass& operator=(MovableClass&& obj) noexcept {
		this->name = std::move(obj.name);
		std::println(std::cout, "MovableClass({}): move assignment called", name);
		return *this;
	}
};

class CopiableAndMovableClass {
public:
	std::string name;
	explicit CopiableAndMovableClass(const std::string_view name) : name(name) {}

	CopiableAndMovableClass(const CopiableAndMovableClass& obj) {
		this->name = obj.name;
		std::println(std::cout, "CopiableAndMovableClass({}): copy constructor called", name);
	}

	CopiableAndMovableClass(CopiableAndMovableClass&& obj) noexcept : name(std::move(obj.name)) {
		std::println(std::cout, "CopiableAndMovableClass({}): move constructor called", name);
	}

	CopiableAndMovableClass& operator=(const CopiableAndMovableClass& obj) {
		this->name = obj.name;
		std::println(std::cout, "CopiableAndMovableClass({}): copy assignment called", name);
		return *this;
	}

	CopiableAndMovableClass& operator=(CopiableAndMovableClass&& obj) noexcept {
		this->name = std::move(obj.name);
		std::println(std::cout, "CopiableAndMovableClass({}): move assignment called", name);
		return *this;
	}
};

int main() {
	{
		static_assert(std::is_copy_constructible_v<SimpleClass>);
		static_assert(std::is_copy_assignable_v<SimpleClass>);
		static_assert(std::is_move_constructible_v<SimpleClass>);
		static_assert(std::is_move_assignable_v<SimpleClass>);
		SimpleClass a{"a"}, b{"b"};

		std::println("Before: a({}) b({})", a.name, b.name);
		std::swap(a, b);
		std::println("After: a({}) b({})", a.name, b.name);
	}
	std::println();

	{
		static_assert(std::is_copy_constructible_v<CopiableClass>);
		static_assert(std::is_copy_assignable_v<CopiableClass>);
		// while move constructor and assignment is not declared, the compiler automatically
		// uses copy constructor as the way to execute move construction and assignment
		static_assert(std::is_move_constructible_v<CopiableClass>);
		static_assert(std::is_move_assignable_v<CopiableClass>);
		CopiableClass a{"a"}, b{"b"};
		std::println("Before: a({}) b({})", a.name, b.name);
		std::swap(a, b);
		std::println("After: a({}) b({})", a.name, b.name);
	}
	std::println();

	{
		static_assert(!std::is_copy_constructible_v<MovableClass>);
		static_assert(!std::is_copy_assignable_v<MovableClass>);
		static_assert(std::is_move_constructible_v<MovableClass>);
		static_assert(std::is_move_assignable_v<MovableClass>);
		MovableClass a{"a"}, b{"b"};
		std::println("Before: a({}) b({})", a.name, b.name);
		std::swap(a, b);
		std::println("After: a({}) b({})", a.name, b.name);
	}
	std::println();

	{
		static_assert(std::is_copy_constructible_v<CopiableAndMovableClass>);
		static_assert(std::is_copy_assignable_v<CopiableAndMovableClass>);
		static_assert(std::is_move_constructible_v<CopiableAndMovableClass>);
		static_assert(std::is_move_assignable_v<CopiableAndMovableClass>);
		CopiableAndMovableClass a{"a"}, b{"b"};
		std::println("Before: a({}) b({})", a.name, b.name);
		std::swap(a, b);
		std::println("After: a({}) b({})", a.name, b.name);
	}
	std::println();

	return 0;
}