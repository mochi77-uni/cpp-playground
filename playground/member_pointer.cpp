
#include <iostream>
#include <vector>

struct Sample {
	double value1;
	double value2;
	double value3;
};

namespace ns {
	/* it's fine to not use std::vector<Sample>::iterator& here as copying iterator is very cheap
	 * and const_iterator makes more sense in this scenario as the function doesn't modify the
	 * content of the member */
	double sum(std::vector<Sample>::const_iterator begin,
			   std::vector<Sample>::const_iterator end,
			   double Sample::* value) {
		double total = 0;
		while (begin != end) {
			const Sample& sample = *begin;
			total += sample.*value;
			++begin;
		}
		return total;
	}

	template<typename Titer, typename S>
	S sum_general(Titer begin, Titer end, S std::iterator_traits<Titer>::value_type::* value) {
		using T = typename std::iterator_traits<Titer>::value_type;
		S total = 0;
		while (begin != end) {
			const T& t = *begin;
			total += t.*value;
			++begin;
		}
		return total;
	}
}

int main() {
	std::vector<Sample> samples = {
		{1.4, 6.3, 8.2},
		{3.7, 2.6, 1.2},
		{7.5, 8.4, 1.5}
	};

	std::print(std::cout, "{}\n", ns::sum(samples.begin(), samples.end(), &Sample::value1));
	std::print(std::cout, "{}\n", ns::sum_general(samples.begin(), samples.end(), &Sample::value1));

	std::print(std::cout,"&samples:\t\t\t{}\n", static_cast<void *>(&samples));
	std::print(std::cout,"&samples[0]:\t\t{}\n", static_cast<void *>(&samples[0]));
	std::print(std::cout,"&samples[0].value1:\t{}\n", static_cast<void *>(&samples[0].value1));
	std::print(std::cout,"&samples[0].value2:\t{}\n", static_cast<void *>(&samples[0].value2));
	std::print(std::cout,"&samples[0].value3:\t{}\n", static_cast<void *>(&samples[0].value3));
	// Cannot print member pointer
	// std::print(std::cout,"Sample::value1:\t{}\n", static_cast<void *>(&Sample::value1));
	// std::print(std::cout,"Sample::value2:\t{}\n", static_cast<void *>(&Sample::value2));
	// std::print(std::cout,"Sample::value3:\t{}\n", static_cast<void *>(&Sample::value3));

	return 0;
}