/*
 * https://codeforces.com/problemset/problem/909/C
 */
#include <bits/stdc++.h>

constexpr uint16_t MAX_LENGTH = 5000;
constexpr uint64_t MODULO = 1000000007;

uint64_t dp[MAX_LENGTH][MAX_LENGTH];
uint64_t count_indentations(const char* s, size_t size) {
	dp[0][0] = 1;
	for (size_t i = 1; i < size; ++i) {
		if (s[i - 1] == 'f') {
			dp[i][0] = 0;
			for (size_t j = 1; j < size; ++j) {
				dp[i][j] = dp[i - 1][j-1];
			}
		} else {
			uint64_t sum = 0;
			for (ssize_t j = i - 1; j != -1; --j) {
				sum += dp[i - 1][j];
				sum %= MODULO;
				dp[i][j] = sum;
			}
		}
	}
	return std::accumulate(std::begin(dp[size - 1]), std::end(dp[size - 1]),
			0ull);
}

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	uint16_t N;
	std::cin >> N;

	char s[MAX_LENGTH + 1];
	for (size_t i = 0; std::cin >> s[i]; ++i);

	std::cout << count_indentations(s, N) % MODULO;

	return 0;
}
