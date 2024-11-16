#include <iostream>
#include <Shapes.h>
#include <iomanip>
#include <Array.h>

int main() {
    auto s1 = Triangle(Triangle<float>({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} }));
    auto s2 = Square(Vertex<float>{ 0.0f, 0.0f }, 100.0f);
    auto s3 = Rectangle(Vertex<float>{ 0.0f, 0.0f }, 100.0f, 100.0f);

    Array<float> container = {
        &s1, &s2, &s3
    };

    for (auto& s : container) {
        std::cout << *static_cast<Polygon<float>*>(s) << std::endl;
    }
}