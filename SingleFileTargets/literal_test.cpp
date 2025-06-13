
#include <iostream>

class Donfan {
	uint32_t times;
public:
	Donfan() : Donfan(0) {}
	Donfan(const uint32_t times) : times(times) {}

	friend std::ostream& operator<<(std::ostream& os, const Donfan& d) {
		for (uint32_t i = 0; i < d.times; i++)
			os << "Donfan";
		return os;
	}
};

Donfan operator""_donfan(unsigned long long times) {
	return Donfan(static_cast<uint32_t>(times));
}

int main() {
	std::cout << 5_donfan << std::endl;

	return 0;
}