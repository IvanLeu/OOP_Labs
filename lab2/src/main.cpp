#include <iostream>
#include <Eleven.h>
#include <string>

int main() {
	size_t s;
	std::cin >> s;

	Eleven el{ s };

	std::string s{ el.ptr };

	std::cout << s;
}