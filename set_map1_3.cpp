#include <iostream>
#include <vector>
#include <map>
#include <sstream>

bool contains(std::vector<int>& nums, int k) {
    std::map<int, int> Index;

    for (int i = 0; i < nums.size(); ++i) {
        if (Index.find(nums[i]) != Index.end() && i - Index[nums[i]] <= k) {
            return true;
        }
        Index[nums[i]] = i;
    }

    return false;
}

int main() {
    std::vector<int> nums;
    int k, num;
    std::string input;

    std::cout << "Elements: ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    while (iss >> num) {
        nums.push_back(num);
    }

    std::cout << "k: ";
    std::cin >> k;

    if (contains(nums, k)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    return 0;
}
