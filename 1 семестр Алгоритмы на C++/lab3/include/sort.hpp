#pragma once

#include <algorithm>
#include <utility>

template <typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare comp) {
    for (T* i = first + 1; i < last; i++) {
        T* j = i - 1;
        while (j >= first && comp(*(j + 1), *j)) {
            std::swap(*(j + 1), *j);
            j -= 1;
        }
    }
}

template <typename T, typename Compare>
T* median_of_three(T* a, T* b, T* c, Compare comp) {
    // comp -> (a < b)

    // a < b
    if (comp(*a, *b)) {
        // a < b < c
        if (comp(*b, *c)) {
            return b;
        }
        // a < c < b
        else if (comp(*a, *c)) {
            return c;
        }
        // c < a < b
        else {
            return a;
        }
    }
    // a >= b
    else {
        // b <= a < c
        if (comp(*a, *c)) {
            return a;
        }
        // b < c < a
        else if (comp(*b, *c)) {
            return c;
        }
        // c < b <= a
        else {
            return b;
        }
    }
}

template <typename T, typename Compare>
T* partition(T* first, T* last, Compare comp) {
    T* mid = first + (last - first) / 2;
    T* pivot_ptr = median_of_three(first, mid, last - 1, comp);

    std::swap(*first, *pivot_ptr);
    T& pivot_ref = *first;

    T* i = first;
    T* j = last;

    while (true) {
        do {
            ++i;
        } while (i < last && comp(*i, pivot_ref));

        do {
            --j;
        } while (j > first && comp(pivot_ref, *j));

        if (i >= j) {
            break;
        }

        std::swap(*i, *j);
    }

    std::swap(*first, *j);
    return j;
}

template <typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
    if (first == last || first + 1 == last) {
        return;
    }

    std::ptrdiff_t insertion_sort_trigger_length = 16;

    while (last - first > insertion_sort_trigger_length) {
        T* pivot = partition(first, last, comp);

        std::ptrdiff_t left_len = pivot - first;
        std::ptrdiff_t right_len = (last - 1) - pivot;

        // Меньше -> рекурсия
        // Больше -> цикл
        if (left_len < right_len) {
            sort(first, pivot, comp);
            first = pivot + 1;
        } else {
            sort(pivot + 1, last, comp);
            last = pivot;
        }
    }

    insertion_sort(first, last, comp);
}
