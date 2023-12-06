#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::set<int> values;

    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        values.insert(num);
    }

    std::cout << values.size() << std::endl;
    return 0;
}
