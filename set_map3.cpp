#include <iostream>
#include <unordered_map>
#include <algorithm>

int substring(std::string s) {
    std::unordered_map<char, int> charindex;
    int maxlength = 0;
    int left = 0;
    int right = 0;

    while (right < s.length()) {
        if (charindex.find(s[right]) != charindex.end() && charindex[s[right]] >= left) {
            left = charindex[s[right]] + 1;
        }
        charindex[s[right]] = right;
        maxlength = std::max(maxlength, right - left + 1);
        right++;
    }

    return maxlength;
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << substring(s)<<std::endl;

    return 0;
}
