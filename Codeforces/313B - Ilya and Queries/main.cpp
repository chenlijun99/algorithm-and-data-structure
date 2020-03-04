/*
 * https://codeforces.com/problemset/problem/313/B
 */

#include <bits/stdc++.h>
using namespace std;

constexpr size_t MAX_LENGTH = 10e5;
char str[MAX_LENGTH + 1];
// array of partial sums. 0-th element is a dummy 0.
uint32_t ps[MAX_LENGTH - 1];

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin.getline(str, MAX_LENGTH + 1, '\n');

    for (size_t i = 1; str[i] != '\0'; ++i) {
        ps[i] = ps[i-1] + (str[i-1] == str[i]);
    }

    uint32_t m;
    cin >> m;

    uint32_t l, r;

    while (std::cin >> l >> r) {
        std::cout << ps[r-1] - ps[l-1] << '\n';
    }

    return 0;
}
