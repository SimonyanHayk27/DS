#include <iostream>
#include <map>

int Palindrome(std::string s) {
    std::map<char, int> freq;

    for (char c : s) {
        freq[c]++;
    }

    int Length = 0;
    bool oddUsed = false;

    for (auto& pair : freq) {
        Length += pair.second / 2 * 2;
        
        if (pair.second % 2 == 1 && !oddUsed) {
            Length++;
            oddUsed = true;
        }
    }

    return Length;
}

int main() {
    std::string input;
    std::cin >> input;
    std::cout << Palindrome(input) << std::endl;
    return 0;
}
