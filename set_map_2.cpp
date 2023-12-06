#include <iostream>
#include <unordered_set>
using namespace std;

int num(string jewels, string stones) {
    unordered_set<char> jewelSet;
    int count = 0;

    for (int i = 0; i < jewels.length(); ++i) {
        jewelSet.insert(jewels[i]);
    }

    for (int i = 0; i < stones.length(); ++i) {
        if (jewelSet.find(stones[i]) != jewelSet.end()) {
            count++;
        }
    }

    return count;
}

int main() {
    string jewels, stones;

    cin >> jewels;
    cin >> stones;

    int result = num(jewels, stones);
    cout << result << endl;

    return 0;
}
