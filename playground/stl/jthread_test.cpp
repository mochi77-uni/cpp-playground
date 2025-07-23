
#include <thread>
#include <atomic>
#include <ranges>
#include <iostream>

void runJthread() {
	using namespace std::literals::chrono_literals;
	using namespace std::views;
	std::jthread jthread([] {
		for (auto i : iota(0) | take(10)) {
			std::print(std::cout, "runJthread: jthread {}\n", i);
			std::this_thread::sleep_for(0.5s);
		}
	});
}
int main () {
	using namespace std::literals::chrono_literals;
	using namespace std::views;

	// std::jthread automatically joins on destruction
	// This means that the function will be blocked until
	// the jthread is finished
	runJthread();

	{
		std::jthread jthread([](const std::stop_token &stopToken) {
			std::stop_callback callback(stopToken, []() {
				std::cout << "stop callback\n";
			});
			while (!stopToken.stop_requested()) {
				std::cout << "working\n";
				std::this_thread::sleep_for(0.5s);
			}
		});
		std::this_thread::sleep_for(3s);
		std::cout << "send stop token\n";
		jthread.request_stop();
	}

	{
		std::thread thread([] {
			for (auto i : iota(0) | take(10)) {
				std::print(std::cout, "thread {}\n", i);
				std::this_thread::sleep_for(0.5s);
			}
		});

		// std::jthread automatically joins on destruction
		// This means the thread will be joined when the jthread object is destroyed
		// at the end of main(), before the program exits
		std::jthread jthread([] {
			for (auto i : iota(0) | take(10)) {
				std::print(std::cout, "jthread {}\n", i);
				std::this_thread::sleep_for(0.5s);
			}
		});

		thread.join();
	}

	return 0;
}
