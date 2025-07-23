
#include <semaphore>
#include <thread>
#include <iostream>
#include <vector>

std::counting_semaphore<3> semaphore{3};
// Binary semaphore is just counting_semaphore<1>
std::binary_semaphore signalMainToWorker(0);
std::binary_semaphore signalWorkerToMain(0);

int main() {
	using namespace std::literals;

	{
		std::vector<std::jthread> workers;
		for (int i = 0; i < 5; ++i) {
			workers.emplace_back([](int i) {
				std::print(std::cout, "Worker {} waiting for resource\n", i);
				if (!semaphore.try_acquire_for(1s)) {
					std::print(std::cout, "Worker {} failed to get resource\n", i);
					return;
				}
				std::cout << "Worker " << i << " acquired resource\n";

				std::this_thread::sleep_for(2s);
				std::cout << "Worker " << i << " released resource\n";
				semaphore.release();
			}, i);
			std::this_thread::sleep_for(100ms);
		}
	}

	{
		std::jthread worker([] {
			std::cout << "Worker waiting for signal\n";
			signalMainToWorker.acquire();
			std::cout << "Worker acquired signal\n";
			std::cout << "Worker working...\n";
			std::this_thread::sleep_for(2s);
			std::cout << "Worker released signal\n";
			signalWorkerToMain.release();
		});
		std::cout << "sleep for 2 seconds before start working\n";
		std::this_thread::sleep_for(2s);
		signalMainToWorker.release();
		signalWorkerToMain.acquire();
	}

	return 0;
}