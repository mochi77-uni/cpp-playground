
#include <chrono>
#include <iostream>
#include <functional>

template<typename T, typename... Args>
auto time_elapsed(std::function<T> func, Args&&... args) {
	const auto start{std::chrono::high_resolution_clock::now()};
	typename std::function<T>::result_type res{func(std::forward<Args>(args)...)};
	const auto end{std::chrono::high_resolution_clock::now()};
	return std::make_pair(end - start, res);
}

template<typename T>
concept is_not_negative = requires(T t) { t >= 0; };

template<typename T> requires is_not_negative<T>
T fibonacci(T n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
	using namespace std::literals::chrono_literals;
	using namespace std::chrono;

	// operator / and literals to construct time variable
	constexpr auto ymd {2000y / July / 7d};
	std::cout << ymd << std::endl;

	for (const hours hour : {0h, 1h, 11h, 12h, 13h, 23h}) {
		const hours am {make12(hour)};
		std::println(std::cout, "{:>3}h ={:>3}h {}", hour.count(), am.count(),
			is_am(hour) ? "am" : "pm");
	}

	const auto now{system_clock::now()};
	std::println(std::cout, "Current time 'UTC' is {}", now);
	std::println(std::cout, "Current time 'Local' is {}", current_zone()->to_local(now));

	const std::function<int(int)> fib_wrapper = [](const int n) { return fibonacci(n); };
	auto [duration, value] = time_elapsed(fib_wrapper, 42);
	std::println(std::cout, "Calculate fib(42) {} uses {:.3f}s", value, std::chrono::duration<double>(duration).count());

	return 0;
}