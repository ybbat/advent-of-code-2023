#include <algorithm>
#include <stack>
#include <unordered_map>
#include <utility>
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
    {NORTH, {-3, 0}},
    {SOUTH, {3, 0}},
    {WEST, {0, -3}},
    {EAST, {0, 3}}
};

std::unordered_map<direction, std::pair<int, int>> smalldirs = {
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

std::unordered_map<char, std::vector<std::vector<char>>> expandmap = {
    {'|', {
        {'.', '|', '.'},
        {'.', '|', '.'},
        {'.', '|', '.'}
    }},
    {'-', {
        {'.', '.', '.'},
        {'-', '-', '-'},
        {'.', '.', '.'}
    }},
    {'7', {
        {'.', '.', '.'},
        {'-', '7', '.'},
        {'.', '|', '.'}
    }},
    {'J', {
        {'.', '|', '.'},
        {'-', 'J', '.'},
        {'.', '.', '.'}
    }},
    {'L', {
        {'.', '|', '.'},
        {'.', 'L', '-'},
        {'.', '.', '.'}
    }},
    {'F', {
        {'.', '.', '.'},
        {'.', 'F', '-'},
        {'.', '|', '.'}
    }},
    {'S', {
        {'.', '.', '.'},
        {'.', 'S', '.'},
        {'.', '.', '.'}
    }}
};

char dirstopipe(direction firstdir, direction seconddir) {
    if (firstdir == NORTH && seconddir == SOUTH) {
       return '|';
   } else if (firstdir == EAST && seconddir == WEST) {
       return '-';
   } else if (firstdir == NORTH && seconddir == EAST) {
       return 'F';
   } else if (firstdir == NORTH && seconddir == WEST) {
       return '7';
   } else if (firstdir == SOUTH && seconddir == WEST) {
       return 'J';
   } else if (firstdir == SOUTH && seconddir == EAST) {
       return 'L';
   } else if (firstdir == SOUTH && seconddir == NORTH) {
       return '|';
   } else if (firstdir == WEST && seconddir == EAST) {
       return '-';
   } else if (firstdir == EAST && seconddir == NORTH) {
       return 'J';
   } else if (firstdir == WEST && seconddir == NORTH) {
       return 'L';
   } else if (firstdir == WEST && seconddir == SOUTH) {
       return 'F';
   } else if (firstdir == EAST && seconddir == SOUTH) {
       return '7';
   } else {
       return '\0';
   }
}

void set3x3(std::vector<std::vector<char>> &expanded, int curry, int currx, char c, bool hash) {
    for (int k = 0; k < expandmap[c].size(); k++) {
        for (int l = 0; l < expandmap[c][k].size(); l++) {
            if (expandmap[c][k][l] != '.') {
                expanded[curry + k - 1][currx + l - 1] = hash ? '#' : expandmap[c][k][l];
            } else {
                expanded[curry + k - 1][currx + l - 1] = '.';
            }
        }
    }
}

std::vector<std::vector<char>> expand(std::vector<std::vector<char>> &input) {
    std::vector<std::vector<char>> expanded(input.size() * 3, std::vector<char>(input[0].size() * 3, '.'));
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            set3x3(expanded, i * 3 + 1, j * 3 + 1, input[i][j], false);
        }
    }
    return expanded;
}

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

void dfs(std::vector<std::vector<char>> &input, int curry, int currx) {
    std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));
    std::stack<std::pair<int, int>> stack;
    stack.push({curry, currx});

    bool edge = false;

    while (!stack.empty()) {
        auto [curry, currx] = stack.top();
        // std::cout << curry << " " << currx << std::endl;
        stack.pop();

        if (visited[curry][currx]) continue;

        visited[curry][currx] = true;

        for (auto dir : smalldirs) {
            int nexty = curry + dir.second.first;
            int nextx = currx + dir.second.second;
            if (nexty < 0 || nextx < 0 || nexty >= input.size() || nextx >= input[nexty].size()) {
                edge = true;
                continue;
            }
            if (input[curry + dir.second.first][currx + dir.second.second] == '.') {
                stack.push({curry + dir.second.first, currx + dir.second.second});
            }
        }
    }

    if (edge) {
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[i].size(); j++) {
                if (visited[i][j]) {
                    input[i][j] = '$';
                }
            }
        }
    }
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

    auto expanded = expand(input);

    for (auto& row : expanded) {
        for (auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    int curry = 0;
    int currx = 0;

    find_start(expanded, curry, currx);
    auto dir = find_first_dir(expanded, curry, currx);
    auto firstdir = dir;
    curry += dirs[dir].first;
    currx += dirs[dir].second;

    do {
        dir = pipeoptions[dir][expanded[curry][currx]];
        set3x3(expanded, curry, currx, expanded[curry][currx], true);
        expanded[curry][currx] = '#';
        curry += dirs[dir].first;
        currx += dirs[dir].second;
    } while (expanded[curry][currx] != 'S');

    auto lastdir = dir;
    auto sdir = dirstopipe(lastdir, firstdir);

    input[curry/3][currx/3] = sdir;

    set3x3(expanded, curry, currx, sdir, true);

    for (auto& row : expanded) {
        for (auto& c : row) {
            if (c != '#' && c != '.') c = '.';
            std::cout << c;
        }
        std::cout << std::endl;
    }

    dfs(expanded, 0, 0);

    std::cout << std::endl;


    for (auto& row : expanded) {
        for (auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    int acc = 0;
    for (int i = 0; i < expanded.size() - 2; i += 3) {
        for (int j = 0; j < expanded[i].size() - 2; j += 3) {
            std::vector<std::reference_wrapper<char>> tocheck = {expanded[i][j], expanded[i][j+1], expanded[i][j+2],
                                         expanded[i+1][j], expanded[i+1][j+1], expanded[i+1][j+2],
                                         expanded[i+2][j], expanded[i+2][j+1], expanded[i+2][j+2]};
            if (std::all_of(tocheck.begin(), tocheck.end(), [](char c) { return c == '.'; })) acc++;

            for (auto& c : tocheck) {
                c.get() = '!';
            }
        }
    }

    std::cout << acc << std::endl;

    return 0;
}