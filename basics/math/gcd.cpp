#include <iostream>

int gcd(int n, int m) {
    if (m == 0) {
        return n;
    }

    return gcd(m , n % m);
}

int main(int argc, char *argv[])
{
    int n, m;
    std::cout << "1st number> ";
    std::cin >> n;
    std::cout << "2nd number> ";
    std::cin >> m;

    std::cout << gcd(n, m) << std::endl;

    return 0;
}
