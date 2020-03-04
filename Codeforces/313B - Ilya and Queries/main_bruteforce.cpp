#include <bits/stdc++.h>

using namespace std;

constexpr size_t MAX_LENGTH = 10e5;

char str[MAX_LENGTH+1];

uint32_t run_query(uint32_t l, uint32_t r) {
    // normalize indexes
    --l;
    --r;

    uint32_t sum = 0;
    for (uint32_t i = l; i < r; ++i) {
        if (str[i] == str[i + 1]) {
            ++sum;
        }
    }

    return sum;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin.getline(str, MAX_LENGTH+1, '\n');

    uint32_t m;
    cin >> m;

    uint32_t l, r;

    while (std::cin >> l >> r) {
        std::cout << run_query(l, r) << '\n';
    }

    return 0;
}
