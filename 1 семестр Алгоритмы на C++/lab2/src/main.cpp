#include <iostream>

#include "array.hpp"

int main() {
    Array<int> arr = Array<int>();

    std::cout << arr.insert(1) << std::endl;
    std::cout << arr.insert(0, 2) << std::endl;
    std::cout << arr.insert(3) << std::endl;

    for (auto iter = arr.iterator(); iter.hasNext(); iter.next()) {
        std::cout << iter.get() << " ";
    }
    std::cout << std::endl;

    for (auto iter = arr.reverseIterator(); iter.hasNext(); iter.next()) {
        std::cout << iter.get() << " ";
    }
    std::cout << std::endl;

    arr.remove(1);
    for (auto iter = arr.iterator(); iter.hasNext(); iter.next()) {
        std::cout << iter.get() << " ";
    }
    std::cout << std::endl;

    arr.remove(1);
    for (auto iter = arr.iterator(); iter.hasNext(); iter.next()) {
        std::cout << iter.get() << " ";
    }
    std::cout << "\n" << std::endl;

    Array<int> a;
    for (int i = 0; i < 10; ++i) {
        a.insert(i + 1);
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] *= 2;
    }
    for (auto it = a.iterator();; it.next()) {
        std::cout << it.get() << std::endl;

        if (!it.hasNext()) {
            break;
        }
    }

    return 0;
}
