#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

std::string sort(std::string s) {
    std::unordered_map<char, int> count;
    for (char c : s) {
        count[c]++;
    }

    std::vector<std::pair<char, int>> frequency;
    for (const auto& entry : count) {
        frequency.push_back(entry);
    }
    std::sort(frequency.begin(), frequency.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::string result;
    for (const auto& entry : frequency) {
        result += std::string(entry.second, entry.first);
    }

    return result;
}

int main() {
    std::string input;

    std::cout << "Input: ";
    std::cin >> input;

    std::cout << "Sorted string: " << sort(input) << std::endl;

    return 0;
}
