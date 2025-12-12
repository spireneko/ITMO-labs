#include <iostream>
#include "sort.hpp"

int main() {
    int a[] = {3, 7, 2, 8, 6, 5, 3, 1};

    sort(a, a + 8, [](int a, int b) { return a < b; });

    for (int i = 0; i < 8; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    int b[] = {3, 7, 2, 8, 6, 5, 3, 1};

    insertion_sort(b, b + 8, [](int a, int b) { return a < b; });

    for (int i = 0; i < 8; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
