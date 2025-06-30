
#include <iostream>
#include <format>
#include <typeinfo>
#include <memory>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

/*
 * Legacy Implementation
 * template <typename T> struct is_prvalue : std::true_type {};
 * template <typename T> struct is_prvalue<T&> : std::false_type {};
 * template <typename T> struct is_prvalue<T&&> : std::false_type {};
 *
 * template <typename T> struct is_lvalue : std::false_type {};
 * template <typename T> struct is_lvalue<T&> : std::true_type {};
 * template <typename T> struct is_lvalue<T&&> : std::false_type {};
 *
 * template <typename T> struct is_xvalue : std::false_type {};
 * template <typename T> struct is_xvalue<T&> : std::false_type {};
 * template <typename T> struct is_xvalue<T&&> : std::true_type {};
 */

template <typename T> inline constexpr bool is_prvalue = std::true_type {};
template <typename T> inline constexpr bool is_prvalue = std::false_type {};
template <typename T> inline constexpr bool is_prvalue = std::false_type {};

template <typename T> inline constexpr bool is_lvalue = std::false_type {};
template <typename T> inline constexpr bool is_lvalue = std::true_type {};
template <typename T> inline constexpr bool is_lvalue = std::false_type {};

template <typename T> inline constexpr bool is_xvalue = std::false_type {};
template <typename T> inline constexpr bool is_xvalue = std::false_type {};
template <typename T> inline constexpr bool is_xvalue = std::true_type {};

#ifdef __GNUC__
namespace cxxabi {
	template <typename T>
	std::string getTypeName() {
		int status;
		std::string typeName = typeid(T).name();
		std::unique_ptr<char, void(*)(void*)> demangleName(
			abi::__cxa_demangle(typeName.c_str(), nullptr, nullptr, &status),
			std::free
		);
		return status == 0 ? demangleName.get() : typeName;
	}
}
#endif

namespace pretty_func {
	namespace impl {
		template <typename T>
		constexpr std::string_view getRawTypeName() {
#ifdef _MSC_VER
			return __FUNCSIG__
			#else
			return __PRETTY_FUNCTION__;
#endif
		}

		struct TypeNameFormat {
			std::size_t junk_leading = 0;
			std::size_t junk_total = 0;
		};

		constexpr TypeNameFormat typeNameFormat = [] {
			std::string_view sample = getRawTypeName<int>();
			return TypeNameFormat {
				.junk_leading = sample.find("int"),
				.junk_total = sample.size() - 3
			};
		} ();

		template <typename T>
		static constexpr auto typeNameStorage = [] () constexpr {
			std::array<char, getRawTypeName<T>().size() - typeNameFormat.junk_total + 1> result {};
			std::copy_n(getRawTypeName<T>().data() + typeNameFormat.junk_leading, result.size() - 1, result.data());
			return result;
		} ();
	}

	template <typename T>
	constexpr std::string_view getTypeName () {
		return {impl::typeNameStorage<T>.data(), impl::typeNameStorage<T>.size() - 1};
	}
}

int main() {
	int a {42};
	// lvalue reference
	int& b {a};
	// rvalue reference, std::move() to cast a as an rvalue, r is still a reference to a
	int&& r {std::move(a)};

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << r << std::endl;

	a = 5;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << r << std::endl;

	static_assert(is_prvalue<decltype(42)>());
	static_assert(is_lvalue<decltype((a))>());
	static_assert(is_xvalue<decltype(std::move(a))>());

	// static_assert(std::is_lvalue_reference<decltype((b))>::value);
	static_assert(std::is_lvalue_reference_v<decltype(b)>);
	static_assert(is_lvalue<decltype((b))>());

	// static_assert(std::is_rvalue_reference<decltype(r)>::value);
	static_assert(std::is_rvalue_reference_v<decltype(r)>);
	static_assert(is_lvalue<decltype((r))>());

#ifdef __GNUC__
	{
		using namespace cxxabi;
		std::cout << "Using cxxabi.h" << std::endl;
		std::cout << std::format("decltype(a)\t=\t{}\n", getTypeName<decltype(a)>());
		std::cout << std::format("decltype((a))\t=\t{}\n", getTypeName<decltype((a))>());
		std::cout << std::format("decltype(b)\t=\t{}\n", getTypeName<decltype(b)>());
		std::cout << std::format("decltype((b))\t=\t{}\n", getTypeName<decltype((b))>());
		std::cout << std::format("decltype(r)\t=\t{}\n", getTypeName<decltype(r)>());
		std::cout << std::format("decltype((r))\t=\t{}\n", getTypeName<decltype((r))>());
	}
#endif

	std::cout << std::endl;

	{
		using namespace pretty_func;
		std::cout << "Using __PRETTY_FUNCTION__" << std::endl;
		std::cout << std::format("decltype(a)\t=\t{}\n", getTypeName<decltype(a)>());
		std::cout << std::format("decltype((a))\t=\t{}\n", getTypeName<decltype((a))>());
		std::cout << std::format("decltype(b)\t=\t{}\n", getTypeName<decltype(b)>());
		std::cout << std::format("decltype((b))\t=\t{}\n", getTypeName<decltype((b))>());
		std::cout << std::format("decltype(r)\t=\t{}\n", getTypeName<decltype(r)>());
		std::cout << std::format("decltype((r))\t=\t{}\n", getTypeName<decltype((r))>());
		std::cout << std::format("decltype(1+1)\t=\t{}\n", getTypeName<decltype(1+1)>());
		std::cout << std::format("decltype(a++)\t=\t{}\n", getTypeName<decltype(a++)>());
		std::cout << std::format("decltype(++a)\t=\t{}\n", getTypeName<decltype(++a)>());
		std::cout << std::format("decltype(&a)\t=\t{}\n", getTypeName<decltype(&a)>());
		std::cout << std::format("decltype(std::move(a))\t=\t{}\n", getTypeName<decltype(std::move(a))>());
	}

	return 0;
}