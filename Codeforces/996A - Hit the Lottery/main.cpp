#include <bits/stdc++.h>

using namespace std;

unsigned bills(vector<unsigned> bill_values, unsigned total) {
    unsigned bills = 0;

    unsigned bills_for_value;
    size_t i = 0;
    while (total > 0) {
        bills_for_value = total / bill_values[i];
        total -= bills_for_value * bill_values[i];
        bills += bills_for_value;
        ++i;
    }

    return bills;
}

int main(int argc, char *argv[])
{
    unsigned n;
    cin >> n;
    cout << bills({100, 20, 10, 5, 1}, n);

    return 0;
}
