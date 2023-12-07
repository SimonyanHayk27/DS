#include <iostream>
#include <map>

int foo(const std::string& s) {
    std::map<char, int> count;

    for (char c : s) {
        count[c]++;
    }

    for (int i = 0; i < s.length(); ++i) {
        if (count[s[i]] == 1) {
            return i;
        }
    }

    return -1; 
}

int main() {
    std::string input;
    std::cin >> input;

    int result = foo(input);

    std::cout << result << std::endl;
    

    return 0;
}
