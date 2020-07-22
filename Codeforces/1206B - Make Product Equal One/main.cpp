#include <bits/stdc++.h>

using namespace std;

uint64_t min_cost_dp(const vector<int> &numbers) {
    uint64_t dp[numbers.size()][2];

    dp[0][0] = std::abs(1 - numbers[0]);
    dp[0][1] = std::abs(-1 - numbers[0]);

    for (size_t i = 1; i < numbers.size(); ++i) {
        dp[i][0] = min(dp[i - 1][0] + std::abs(1 - numbers[i]),
                       dp[i - 1][1] + std::abs(-1 - numbers[i]));
        dp[i][1] = min(dp[i - 1][0] + std::abs(-1 - numbers[i]),
                       dp[i - 1][1] + std::abs(1 - numbers[i]));
    }

    return dp[numbers.size() - 1][0];
}

uint64_t min_cost(const vector<int> &numbers) {
    uint64_t total_cost = 0;
    unsigned negative_count = 0;
    unsigned zero_count = 0;

    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] < 0) {
            total_cost += -1 - numbers[i];
            ++negative_count;
        } else if (numbers[i] == 0) {
            ++zero_count;
        } else {
            total_cost += numbers[i] - 1;
        }
    }

    if (negative_count % 2 != 0 && zero_count > 0) {
        total_cost += 1;
        negative_count++;
        zero_count--;
    }
    total_cost += zero_count;
    if (negative_count % 2 != 0) {
        total_cost += 2;
    }
    return total_cost;
}

int main(int argc, char *argv[]) {
    unsigned n;
    cin >> n;

    vector<int> numbers(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << min_cost_dp(numbers);

    return 0;
}
