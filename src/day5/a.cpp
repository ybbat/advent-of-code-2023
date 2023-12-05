#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<long> parsenums(std::string str) {
    std::vector<long> nums;
    std::stringstream ss(str);
    long num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

int main(int argc, char* argv[])
{
    long acc = 0;

    std::string line;

    std::getline(std::cin, line);
    std::vector<long> seeds = parsenums(line.substr(line.find(":") + 1));

    std::vector<long> before = seeds;
    std::vector<long> after = seeds;

    std::getline(std::cin, line); // skip next line

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            before = after;
        } else if (isdigit(line[0])) {
            std::vector map = parsenums(line);
            long dest = map[0];
            long source = map[1];
            long amount = map[2];

            for (long i = 0; i < before.size(); i++) {
                if (before[i] >= source && before[i] < source + amount) {
                    after[i] += dest - source;
                }
            }
        }
    }

    std::cout << *std::min_element(after.begin(), after.end()) << std::endl;
}