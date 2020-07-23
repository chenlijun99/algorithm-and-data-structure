#include <bits/stdc++.h>

using namespace std;

uint64_t max_score(vector<uint32_t> numbers) {
    uint32_t cnt[100001] = {};

    uint32_t max_number = numeric_limits<uint32_t>::min();
    for (size_t i = 0; i < numbers.size(); ++i) {
        cnt[numbers[i]]++;
        if (max_number < numbers[i]) {
            max_number = numbers[i];
        }
    }

    uint64_t dp[max_number + 1];
    dp[0] = 0;
    dp[1] = cnt[1];

    for (size_t i = 2; i < max_number + 1; ++i) {
        dp[i] = max(dp[i - 1], dp[i - 2] + static_cast<uint64_t>(cnt[i]) * i);
    }

    return dp[max_number];
}

int main(int argc, char *argv[]) {
    uint32_t n;
    cin >> n;

    vector<uint32_t> numbers(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << max_score(numbers);

    return 0;
}
