#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<long> parsenums(std::string str) {
    std::vector<long> nums;
    std::stringstream ss(str);
    long num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

std::vector<long> diffs(std::vector<long> &nums) {
    std::vector<long> diffs;
    for (int i = 1; i < nums.size(); i++) {
        diffs.push_back(nums[i] - nums[i - 1]);
    }
    return diffs;
}

long extrapolate(std::vector<long> &nums) {
    auto d = diffs(nums);
    if (std::all_of(d.begin(), d.end(), [](long i) { return i == 0; })) {
        return nums.back();
    } else {
        return nums.back() + extrapolate(d);
    }
}

int main(int argc, char const *argv[]) {
    std::string input;

    long acc = 0;

    while (std::getline(std::cin, input)) {
        auto nums = parsenums(input);
        acc += extrapolate(nums);
    }

    std::cout << acc << std::endl;

    return 0;
}