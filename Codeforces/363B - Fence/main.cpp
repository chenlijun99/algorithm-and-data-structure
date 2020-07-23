#include <bits/stdc++.h>

using namespace std;

size_t k_min_consecutive_sum(const vector<uint32_t> &planks, size_t k) {
    uint32_t dp[planks.size() - k + 1];
    memset(dp, 0, sizeof(dp));

    size_t index_min_so_far = 0;
    for (size_t i = 0; i < k; ++i) {
        dp[0] += planks[i];
    }

    for (size_t i = 1; i < planks.size() - k + 1; ++i) {
        dp[i] = dp[i - 1] - planks[i - 1] + planks[i + k - 1];
        if (dp[i] < dp[index_min_so_far]) {
            index_min_so_far = i;
        }
    }
    return index_min_so_far + 1;
}

size_t k_min_consecutive_sum_optimized(const vector<uint32_t> &planks,
                                       size_t k) {
    uint32_t dp_last_sum;
    uint32_t dp_last_min_sum;
    size_t index_min_so_far = 0;

    for (size_t i = 0; i < k; ++i) {
        dp_last_sum += planks[i];
    }
    dp_last_min_sum = dp_last_sum;

    for (size_t i = 1; i < planks.size() - k + 1; ++i) {
        dp_last_sum = dp_last_sum - planks[i - 1] + planks[i + k - 1];
        if (dp_last_sum < dp_last_min_sum) {
            dp_last_min_sum = dp_last_sum;
            index_min_so_far = i;
        }
    }

    return index_min_so_far + 1;
}

int main(int argc, char *argv[]) {
    size_t n;
    size_t k;
    cin >> n >> k;

    vector<uint32_t> planks(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> planks[i];
    }

    cout << k_min_consecutive_sum(planks, k);
    return 0;
}
