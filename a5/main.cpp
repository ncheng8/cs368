#include <iostream>
#include "Vector.hpp"

int main() {
    std::cout << "Testing a Vector class, part 1" << std::endl;
    Vector<int> v1;
    std::cout << "size of v1 is : " << v1.Size() << std::endl;

    return 0;
}