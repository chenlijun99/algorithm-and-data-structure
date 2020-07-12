#include <algorithm>
#include <iostream>

void print(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void print_permutations_rec(int *a, size_t size, size_t i) {
    if (i == 0) {
        print(a, size);
        return;
    }

    for (size_t j = 0; j <= i; ++j) {
        std::swap(a[j], a[i]);
        print_permutations_rec(a, size, i - 1);
        std::swap(a[j], a[i]);
    }
}

void print_permutations(int *a, size_t size) {
    size_t i = size - 1;
    print_permutations_rec(a, size, i);
}

int main(int argc, char *argv[]) {
    int a[] = {1, 2, 3, 4};

    print_permutations(a, sizeof(a) / sizeof(a[0]));

    return 0;
}
