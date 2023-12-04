#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <sstream>

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

    std::string line;
    while (std::getline(std::cin, line)) {
        size_t begin = line.find(":") + 1;
        size_t sep = line.find("|");

        std::set<int> first = parsenums(line.substr(begin, sep-begin));
        std::set<int> second = parsenums(line.substr(sep+1));

        std::set<int> intersect;
        std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::inserter(intersect, intersect.begin()));
        if (intersect.size() > 0) acc += pow(2, intersect.size()-1);
    }

    std::cout << acc;
}