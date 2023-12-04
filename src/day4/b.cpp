#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <array>

std::set<int> parsenums(std::string str) {
    std::set<int> nums;
    std::stringstream ss(str);
    int num;
    while (ss >> num) {
        nums.insert(num);
    }
    return nums;
}

int main(int argc, char* argv[])
{
    int acc = 0;

    std::array<int, 10> counts;
    std::fill(counts.begin(), counts.end(), 1);

    int card = 1;
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t begin = line.find(":") + 1;
        size_t sep = line.find("|");

        std::set<int> first = parsenums(line.substr(begin, sep-begin));
        std::set<int> second = parsenums(line.substr(sep+1));

        std::set<int> intersect;
        std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::inserter(intersect, intersect.begin()));


        int amount = counts[0];
        acc += amount;

        std::rotate(counts.begin(), counts.begin()+1, counts.end());
        counts.back() = 1;

        for (int i = 0; i < intersect.size(); i++) {
            counts[i] += amount;
        }

        card++;
    }

    std::cout << acc;
}