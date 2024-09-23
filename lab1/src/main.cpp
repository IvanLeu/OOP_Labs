#include <iostream>
#include <utils.hpp>

int main() {
	std::string input;

	std::cin >> input;

	std::cout << extract_digits(input);
}