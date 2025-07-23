
#include <iostream>

// the most basic iterator requires increment and dereference operator
struct my_input_iterator {
	using difference_type = int;
	using value_type = int;

	auto operator++() -> my_input_iterator&;
	auto operator++(int) -> my_input_iterator;
	auto operator*() const -> int&;
};

// iterator that can be used in for-range, requires equality operator
struct my_forward_iterator {
	using difference_type = int;
	using value_type = int;

	auto operator++() -> my_forward_iterator&;
	auto operator++(int) -> my_forward_iterator;
	auto operator*() const -> int&;
	auto operator==(const my_forward_iterator&) const -> bool;
};

// iterator that can go in an inverse direction, requires decrement operator
struct my_directional_iterator {
	using difference_type = int;
	using value_type = int;

	auto operator++() -> my_directional_iterator&;
	auto operator++(int) -> my_directional_iterator;
	auto operator--() -> my_directional_iterator&;
	auto operator--(int) -> my_directional_iterator;	// New
	auto operator*() const -> int&;
	auto operator==(const my_directional_iterator&) const -> bool;
};

// iterator that can access value by index, requires stricter comparing and index access operator
struct my_random_access_iterator {
	using difference_type = int;
	using value_type = int;

	auto operator++() -> my_random_access_iterator&;
	auto operator++(int) -> my_random_access_iterator;
	auto operator--() -> my_random_access_iterator&;
	auto operator--(int) -> my_random_access_iterator;
	auto operator*() const -> int&;
	auto operator==(const my_random_access_iterator&) const -> bool;
	auto operator<=>(const my_random_access_iterator&) const -> std::strong_ordering;	// New

	friend auto operator-(const my_random_access_iterator&, const my_random_access_iterator&)
		-> difference_type;		// New
	auto operator+=(difference_type) -> my_random_access_iterator&;		// New
	auto operator-=(difference_type) -> my_random_access_iterator&;		// New
	auto operator+(difference_type) const -> my_random_access_iterator;		// New
	auto operator-(difference_type) const -> my_random_access_iterator;		// New
	friend auto operator+(difference_type, const my_random_access_iterator&)
		-> my_random_access_iterator;	// New
	auto operator[](difference_type) const -> int&;	// New
};

int main() {
	static_assert(std::input_iterator<my_input_iterator>);
	static_assert(std::forward_iterator<my_forward_iterator>);
	static_assert(std::bidirectional_iterator<my_directional_iterator>);
	static_assert(std::random_access_iterator<my_random_access_iterator>);

	return 0;
}