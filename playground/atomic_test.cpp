
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> gCounter = 0;

void incCounter() {
	static constexpr int times = 1000;
	for	(int i = 0; i < times; i++) {
		++gCounter;
	}
}

int main() {
	constexpr int threadCount = 10;

	std::vector<std::thread> threads;
	for (int i = 0; i < threadCount; i++)
		threads.emplace_back(incCounter);

	for (auto& thread : threads) {
		thread.join();
	}

	std::cout << "Final Count: " << gCounter << std::endl;

	return 0;
}