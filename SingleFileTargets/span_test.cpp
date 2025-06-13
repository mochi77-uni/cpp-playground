
#include <iostream>
#include <numeric>
#include <span>
#include <python3.12/Python.h>
#include <python3.12/bytearrayobject.h>

void basicSpanTest() {
	constexpr size_t length{10};
	int* cArray = new int[length] {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	// Unsafe
	for (int i = 0; i < length; i++)
		std::cout << cArray[i] << " ";
	std::cout << '\n';

	// Safe
	std::span<int> spanArray(cArray, length);
	for (const auto i : spanArray)
		std::cout << i << " ";
	std::cout << '\n';

	delete[] cArray;
}

void pythonSpanTest() {
	Py_Initialize();

	try {
		constexpr Py_ssize_t length{10};
		PyObject* pArray = PyByteArray_FromStringAndSize(nullptr, length);
		if (!pArray)
			throw std::runtime_error("Failed to create PyByteArray from string");

		char* data = PyByteArray_AsString(pArray);

		std::span<char> spanArray(data, length);
		std::iota(spanArray.begin(), spanArray.end(), 1);
		for (const char v : spanArray)
			std::cout << static_cast<int>(v) << " ";
		std::cout << '\n';

	} catch (const std::exception& err) {
		std::cerr << err.what() << '\n';
	}
	Py_Finalize();
}

int main() {
	// basicSpanTest();
	pythonSpanTest();

	return 0;
}