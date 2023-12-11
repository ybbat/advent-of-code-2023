#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

void printgrid(std::vector<std::vector<char>> &input) {
    for (auto row : input) {
        for (auto c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<char>> input;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::vector<char> row(line.begin(), line.end());
        if (row.size() > 0) input.push_back(row);
        if (std::all_of(row.begin(), row.end(), [](char c) { return c == '.'; })) {
            input.push_back(row);
        };
    }

    printgrid(input);

    for (int i = 0; i < input[0].size(); i++) {
        bool blank = true;
        for (int j = 0; j < input.size(); j++) {
            if (input[j][i] != '.') {
                blank = false;
                break;
            }
        }
        if (blank) {
            for (int j = 0; j < input.size(); j++) {
                input[j].emplace(input[j].begin() + i, '.');
            }
            i++;
        }
    }

    printgrid(input);

    std::vector<std::pair<size_t, size_t>> coords;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == '#') {
                coords.push_back(std::make_pair(i, j));
            }
        }
    }

    long acc = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i + 1; j < coords.size(); j++) {
            acc += std::abs((int)(coords[i].first - coords[j].first)) + std::abs((int)(coords[i].second - coords[j].second));
        }
    }
    std::cout << acc << std::endl;
}