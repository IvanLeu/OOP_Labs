#include <iostream>
#include <Shapes.h>
#include <iomanip>
#include <Array.h>

int main() {
    auto s1 = std::make_unique<Triangle<float>>(Triangle<float>({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} }));
    auto s2 = std::make_unique<Square<float>>(Vertex<float>{ 0.0f, 0.0f }, 100.0f);
    auto s3 = std::make_unique<Rectangle<float>>(Vertex<float>{ 0.0f, 0.0f }, 100.0f, 100.0f);

    Array<Shape<float>*> container = {
        s1.get(), s2.get(), s3.get()
    };

    container.push_back(s1.get());

    for (auto& s : container) {
        std::cout << *reinterpret_cast<Polygon<float>*>(s) << std::endl;
    }
}