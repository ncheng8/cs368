#include <iostream>
#include "Vector.hpp"

int main() {
    std::cout << "Testing a Vector class, part 1" << std::endl;
    Vector<int> v1;
    v1.Push_Back(77);
    v1.Push_Back(88);
    v1.Push_Back(99);

    std::cout << "size of v1 is : " << v1.Size() << std::endl;

    std::cout << "capacity of v1 is : " << v1.Capacity() << std::endl;
    std::cout << "v1 is Empty value : " << v1.Empty() << std::endl;
    return 0;
}