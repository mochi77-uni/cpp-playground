
#include <iostream>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

int main() {
	glm::vec2 v1(5.0, 7.0);
	glm::mat2x2 m1(1.0, 0.0, 0.0, 1.0);

	std::cout << glm::to_string(v1) << std::endl;
	std::cout << glm::to_string(m1) << std::endl;
	std::cout << glm::to_string(v1 * m1) << std::endl;
	std::cout << "length(v1) = " << glm::length(v1) << std::endl;
	std::cout << "normalize(v1) = " << glm::to_string(glm::normalize(v1)) << std::endl;


	return 0;
}