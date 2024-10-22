#include <iostream>
#include <Shapes.h>
#include <iomanip>

int main() {
	Triangle t({ {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} });
	Triangle t2({ {1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f} });

	std::cout << std::boolalpha << (t == t2);
}