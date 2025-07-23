
#include <iostream>

class Widget {
	int data;
public:
	Widget() : Widget(0) {}

	explicit Widget(const int data) : data(data) {
		std::cout << "Default constructor called\n";
	}

	Widget(const Widget& w) : data(w.data) {
		std::cout << "Copy constructor called\n";
	}

	Widget(Widget&& w) noexcept : data(w.data) {
		std::cout << "Move constructor called\n";
		w.data = 0;
	}

	[[nodiscard]] int get_data() const {
		return data;
	}
};

class Handler {
	class HandlerImpl {
		friend class Handler;
		static void handle_widget(const Widget& widget) {
			std::cout << "handled by lvalue reference, data = " << widget.get_data() << '\n';
		}

		static void handle_widget(Widget&& widget) {
			std::cout << "handled by rvalue reference, data = " << widget.get_data() << '\n';
		}
	};
public:
	template<typename T>
	void handle_widget(T&& widget) {
		HandlerImpl::handle_widget(std::forward<T>(widget));
	}
};

int main() {
	Widget w(10);
	std::cout << std::format("w.data\t= {}\n", w.get_data());

	Widget w2 = w;
	std::cout << "w2 copy constructed by w\n";
	std::cout << std::format("w.data\t= {}\n", w.get_data());
	std::cout << std::format("w2.data\t= {}\n", w2.get_data());

	Widget w3 = std::move(w);
	std::cout << "w3 move constructed by w\n";
	std::cout << std::format("w.data\t= {}\n", w.get_data());
	std::cout << std::format("w2.data\t= {}\n", w2.get_data());
	std::cout << std::format("w3.data\t= {}\n", w3.get_data());

	Handler handler;
	handler.handle_widget(w);
	handler.handle_widget(Widget(5));
	handler.handle_widget(std::move(w));

	return 0;
}