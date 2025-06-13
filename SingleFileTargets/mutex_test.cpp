
#include <iostream>
#include <thread>
#include <mutex>
#include <format>
#include <vector>

int gCounter = 0;
std::mutex counterMutex;

void incCounter() {
	constexpr static int times = 100;
	for (int i = 0; i < times; i++) {
		counterMutex.lock();
		gCounter++;
		counterMutex.unlock();
	}
}

void incCounterWithGuardLock() {
	constexpr static int times = 100;
	for (int i = 0; i < times; i++) {
		std::lock_guard<std::mutex> lock(counterMutex);
		gCounter++;
	}
}

int main() {
	std::vector<std::thread> threads;
	constexpr int threadCount = 10;
	for (int i = 0; i < threadCount; i++) {
		threads.emplace_back(incCounterWithGuardLock);
	}

	for (auto& thread : threads) {
		thread.join();
	}

	std::cout << std::format("Final value: {}\n", gCounter);

	return 0;
}