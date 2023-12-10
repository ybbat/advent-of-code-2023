#include <unordered_map>
#include <vector>
#include <iostream>

enum direction {NORTH, SOUTH, WEST, EAST};

std::ostream& operator<<(std::ostream& os, const direction& dir) {
    switch (dir) {
        case NORTH:
            os << "NORTH";
            break;
        case SOUTH:
            os << "SOUTH";
            break;
        case WEST:
            os << "WEST";
            break;
        case EAST:
            os << "EAST";
            break;
    }
    return os;
}

std::unordered_map<direction, std::pair<int, int>> dirs = {
    {NORTH, {-1, 0}},
    {SOUTH, {1, 0}},
    {WEST, {0, -1}},
    {EAST, {0, 1}}
};

std::unordered_map<direction, std::unordered_map<char, direction>> pipeoptions = {
    {NORTH, {{'|', NORTH}, {'7', WEST}, {'F', EAST}}},
    {SOUTH, {{'|', SOUTH}, {'J', WEST}, {'L', EAST}}},
    {WEST, {{'-', WEST}, {'L', NORTH}, {'F', SOUTH}}},
    {EAST, {{'-', EAST}, {'7', SOUTH}, {'J', NORTH}}}
};

void find_start(std::vector<std::vector<char>> &input, int &curry, int &currx) {
    for (curry = 0; curry < input.size(); curry++) {
        for (currx = 0; currx < input[curry].size(); currx++) {
            if (input[curry][currx] == 'S') {
                return;
            }
        }
    }
    throw "No starting point found!";
}

direction find_first_dir(std::vector<std::vector<char>> &input, int &curry, int &currx) {
    for (auto dir : pipeoptions) {
        for (auto option : dir.second) {
            if (input[curry + dirs[dir.first].first][currx + dirs[dir.first].second] == option.first) {
                return dir.first;
            }
        }
    }
    throw "No starting direction found!";
}


int main(int argc, char const *argv[])
{
    std::vector<std::vector<char>> input;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::vector<char> row(line.begin(), line.end());
        if (row.size() > 0) input.push_back(row);
    }

    int curry = 0;
    int currx = 0;

    find_start(input, curry, currx);
    auto dir = find_first_dir(input, curry, currx);
    curry += dirs[dir].first;
    currx += dirs[dir].second;
    std::cout << curry << ", " << currx << std::endl;
    std::cout << dir << std::endl;

    int step = 1;

    do {
        std::cout << curry << ", " << currx << ": " << input[curry][currx] << std::endl;
        dir = pipeoptions[dir][input[curry][currx]];
        std::cout << "heading " << dir << std::endl;

        // dir = pipeoptions[dir][input[curry][currx]];

        curry += dirs[dir].first;
        currx += dirs[dir].second;

        std::cout << "to " << curry << ", " << currx << ": " << input[curry][currx] << std::endl;

        step++;
        std::cout << std::endl;
    } while (input[curry][currx] != 'S');

    std::cout << step / 2 << std::endl;
    return 0;
}