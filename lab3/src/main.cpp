#include <iostream>
#include <Shapes.h>
#include <iomanip>

int main() {
    auto s1 = Triangle(Triangle({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} }));
    auto s2 = Square(Vertex{ 0.0f, 0.0f }, 100.0f);
    auto s3 = Rectangle(Vertex{ 0.0f, 0.0f }, 100.0f, 100.0f);

    std::vector<Polygon*> container = {
        &s1, &s2, &s3
    };

    for (auto& s : container) {
        std::cout << *s << std::endl;
    }
}