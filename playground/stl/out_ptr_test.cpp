
#include <memory>
#include <print>

// Simulate C-style API
extern "C" {
	struct Resource {
		int value;
	};

	bool create_resource(Resource** res_ptr, int initial_value) {
		*res_ptr = (Resource *) malloc(sizeof(Resource));
		if (*res_ptr == nullptr) return false;
		(*res_ptr)->value = initial_value;
		return true;
	}

	void destroy_resource(Resource* res_ptr) {
		free(res_ptr);
	}
}

void allocate_without_out_ptr() {
	std::unique_ptr<Resource, decltype(&destroy_resource)> resource {
		nullptr, destroy_resource
	};

	Resource* raw_ptr = nullptr;
	if (create_resource(&raw_ptr, 32)) {
		resource.reset(raw_ptr);
		std::println("Resource created with value: {}", resource->value);
	}
}

void allocate_with_out_ptr() {
	std::unique_ptr<Resource, decltype(&destroy_resource)> resource {
		nullptr, destroy_resource
	};

	if (create_resource(std::out_ptr(resource), 32)) {
		std::println("Resource created with value: {}", resource->value);
	}
}

int main() {
	allocate_without_out_ptr();
	allocate_with_out_ptr();

	return 0;
}