#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    if (!vec.empty()) {
        os << vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            os << ", " << vec[i];
        }
    }
    os << "]";
    return os;
}


#define SHOW(expr) std::cout << #expr << ": " << (expr) << std::endl


std::vector<int> parsenums(std::string& str) {
    for (auto& c : str) {
        if (c == ',') {
            c = ' ';
        }
    }
    std::vector<int> nums;
    std::stringstream ss(str);
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

void parse(std::vector<std::string> &conditions, std::vector<std::vector<int>> &groups) {
    std::string line;

    while (std::getline(std::cin, line)) {
        size_t space = line.find(" ");
        std::string before(line.begin(), line.begin() + space);
        conditions.push_back(before);
        std::string after(line.begin() + space + 1, line.end());
        groups.push_back(parsenums(after));
    }
}

std::string placegroup(std::string string, int start, int group_size) {

    std::string result = string;
    for (int i = 0; i <  start + group_size; i++) {
        if (i < start) {
            if (result[i] == '?') result[i] = '.';
        } else {
            result[i] = '#';
        }
    }
    return result;

}

bool placeable(std::string string, int start, int group_size) {
    if (start + group_size > string.size()) {
        return false;
    }
    // can't overlap .
    for (int i = start; i < start + group_size; i++) {
        if (string[i] == '.') {
            return false;
        }
    }
    // reveals location of block
    if (start > 0 && string[start - 1] == '#') {
        return false;
    }
    if (start + group_size < string.size() && string[start + group_size] == '#') {
        return false;
    }
    return true;
}

bool check(std::string& conditions, std::vector<int> constraints) {
    int group = 0;
    int group_size = 0;
    int j = 0;
    for (int i = 0; i < conditions.size(); i++) {


        group_size = constraints[j];

        if (conditions[i] == '#') {
            group++;
        } else if (group > 0) {
            if (group != group_size) {
                return false;
            }
            if (group == group_size) {
                j++;
            }
            group = 0;
        }
    }
    if (group > 0 && group == group_size) {
        j++;
    }
    if (j != constraints.size()) {
        return false;
    }
    return true;
}


int solve(std::string conditions, std::vector<int> constraints, int i, int j) {
    if (check(conditions, constraints)) {
        for (int k = 0; k < conditions.size(); k++) {
            if (conditions[k] == '?') {
                conditions[k] = '.';
            }
        }
        std::cout << conditions << std::endl;
        return 1;
    }
    int acc = 0;
    int group_size = constraints[j];
    for (int k = i; k < conditions.size(); k++) {
        if (placeable(conditions, k, group_size)) {
            std::string new_conditions = placegroup(conditions, k, group_size);
            acc += solve(new_conditions, constraints, k + group_size + 1, j + 1);
            if (conditions[k] == '#') {
                break;
            }
        }
    }
    return acc;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> conditions;
    std::vector<std::vector<int>> groups;

    parse(conditions, groups);

    long acc = 0;
    for (int i = 0; i < conditions.size(); i++) {
        long solved = solve(conditions[i], groups[i], 0, 0);
        acc += solved;
        std::cout << solved << std::endl << std::endl;
    }
    std::cout << acc << std::endl;
}