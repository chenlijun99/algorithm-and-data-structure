#include <bits/stdc++.h>

using namespace std;

enum AllowedActivity : short {
    NO_GYM_NO_CONTEST,
    NO_GYM_CONTEST,
    GYM_NO_CONTEST,
    GYM_CONTEST
};

enum ChosenActivity : short {
    REST,
    GO_CONTEST,
    GO_GYM,
};

uint32_t min_rest(const vector<short> &days) {
    uint32_t dp[days.size()][3];
    memset(dp, 0, sizeof(dp));

    dp[0][REST] = 0;
    dp[0][GO_CONTEST] = days[0] == NO_GYM_CONTEST || days[0] == GYM_CONTEST;
    dp[0][GO_GYM] = days[0] == GYM_NO_CONTEST || days[0] == GYM_CONTEST;

    size_t i = 1;
    for (; i < days.size(); ++i) {
        dp[i][REST] =
            max({dp[i - 1][REST], dp[i - 1][GO_CONTEST], dp[i - 1][GO_GYM]});
        if (days[i] == NO_GYM_CONTEST || days[i] == GYM_CONTEST) {
            dp[i][GO_CONTEST] = max({dp[i - 1][REST], dp[i - 1][GO_GYM]}) + 1;
        }

        if (days[i] == GYM_NO_CONTEST || days[i] == GYM_CONTEST) {
            dp[i][GO_GYM] = max({dp[i - 1][REST], dp[i - 1][GO_CONTEST]}) + 1;
        }
    }

    return days.size() -
           max({dp[i - 1][REST], dp[i - 1][GO_CONTEST], dp[i - 1][GO_GYM]});
}

int main(int argc, char *argv[]) {
    uint32_t n;
    cin >> n;

    vector<short> days(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> days[i];
    }

    cout << min_rest(days);

    return 0;
}
