#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

const int expansion = 1000000;

void printgrid(std::vector<std::vector<char>> &input) {
    for (auto row : input) {
        for (auto c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool rowempty(std::vector<std::vector<char>> &input, int row) {
    return std::all_of(input[row].begin(), input[row].end(), [](char c) { return c == '.'; });
}

bool colempty(std::vector<std::vector<char>> &input, int col) {
    for (int j = 0; j < input.size(); j++) {
        if (input[j][col] != '.') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<char>> input;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::vector<char> row(line.begin(), line.end());
        if (row.size() > 0) input.push_back(row);
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

    std::vector<int> expandedcols(input[0].size());
    int col = 0;
    for (int i = 0; i < input[0].size(); i++) {
        if (colempty(input, i)) {
            col += expansion;
        } else {
            col++;
        }
        expandedcols[i] = col;
    }

    std::vector<int> expandedrows(input.size());
    int row = 0;
    for (int i = 0; i < input.size(); i++) {
        if (rowempty(input, i)) {
            row += expansion;
        } else {
            row++;
        }
        expandedrows[i] = row;
    }

    long acc = 0;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = i + 1; j < coords.size(); j++) {
            long expandedyi = expandedrows[coords[i].first];
            long expandedxi = expandedcols[coords[i].second];
            long expandedyj = expandedrows[coords[j].first];
            long expandedxj = expandedcols[coords[j].second];
            acc += std::abs((int)(expandedyi - expandedyj)) + std::abs((int)(expandedxi - expandedxj));
        }
    }
    std::cout << acc << std::endl;
}