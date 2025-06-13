
#include <future>
#include <iostream>

int task_func() {
	sleep(3);
	return 10;
}

void promise_func(std::promise<int>& p) {
	sleep(3);
	p.set_value_at_thread_exit(10);
}

int main() {
	std::packaged_task<int()> task(task_func);
	std::future<int> f = task.get_future();
	std::thread t(std::move(task));

	std::future<int> f2 = std::async(std::launch::async, task_func);

	std::promise<int> p;
	std::future<int> f3 = p.get_future();
	std::thread(promise_func, std::ref(p)).detach();

	f.wait();
	f2.wait();
	f3.wait();

	std::cout << f.get() << std::endl;
	std::cout << f2.get() << std::endl;
	std::cout << f3.get() << std::endl;
	t.join();

	return 0;
}