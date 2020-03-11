/*
 * https://codeforces.com/problemset/problem/44/E
 */

#include <bits/stdc++.h>

using namespace std;

constexpr uint16_t MAX_LENGTH = 200;

unordered_map<uint16_t, unordered_map<uint16_t, int16_t>> table;

int split(uint16_t length, uint16_t k, const uint16_t a, const uint16_t b, std::vector<uint16_t> &solution) {
    {
        double partition = (double)length / k;
        if (floor(partition) < a || ceil( partition ) > b) {
            return -1;
        } else if (k == 1) {
            solution.push_back(length);
            return length;
        }
    }

    if (table.find(length) != table.end() && table[length].find(k) != table[length].end()) {
        return table[length][k];
    }

    for (auto i = a; i <= b; ++i) {
        int ret = split(length - i, k - 1, a, b, solution);
        if (ret != -1) {
            solution.push_back(i);
            return (table[length][k] = i);
        }
    }

    return (table[length][k] = -1);
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint16_t a, b, k;
    std::vector<uint16_t> solution;
    solution.reserve(MAX_LENGTH);
    cin >> k >> a >> b;

    std::string line;
    line.reserve(MAX_LENGTH);
    cin.ignore();
    getline(cin, line);

    int ret = split(line.size(), k, a, b, solution);

    if (ret == -1) {
        cout << "No solution";
    } else {
        uint16_t pos = 0;
        for (auto it = solution.crbegin(); it != solution.rend(); ++it) {
            cout << line.substr(pos, *it) << '\n';
            pos += *it;
        }
    }

    return 0;
}
