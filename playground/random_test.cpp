
#include <iomanip>
#include <iostream>
#include <map>
#include <random>

int main() {
	// non-deterministic random number
	std::random_device rd;

	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> distribution(1, 6);
	int mean = distribution(engine);
	std::cout << "mean:" << mean << '\n';

	std::seed_seq seed2 {rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
	std::mt19937 engine2(seed2);
	std::normal_distribution<> normal_dist(mean, 2);

	std::map<int, int> hist;
	for (int i = 0; i < 30000; i++)
		hist[std::round(normal_dist(engine2))]++;

	std::cout << "hist:\n" << std::fixed << std::setprecision(1);
	for (auto [key, value] : hist)
		std::cout << std::setw(2) << key << ' ' << std::setw(7) << value << ' '
				  << std::string(value / 200, '*') << '\n';

	std::cout << "generate 10 uint32_t using std::seed_seq.generate()\n";
	std::vector<std::uint32_t> list(10);
	seed2.generate(list.begin(), list.end());
	for (const auto& val : list)
		std::cout << val << '\n';

	std::cout << "generate 10 float using std::generate_canonical()\n";
	std::cout << std::setprecision(std::numeric_limits<float>::max_digits10);
	for (int i = 0; i < 10; i++)
		std::cout << std::generate_canonical<float, 10>(engine2) << '\n';

	return 0;
}