#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

int parsenum(std::vector<std::vector<char>> input, int i, int j) {
    int start = 0;
    while (start+j >= 0 && isdigit(input[i][j+start])) {
        start--;
    }
    start++;

    int end = 0;
    while (end+j < input[i].size() && isdigit(input[i][j+end])) {
        end++;
    }
    end--;

    int num = 0;
    int exp = 0;
    for (int l = end; l >= start; l--) {
        num += (input[i][j+l] - '0') * pow(10, exp++);
    }

    return num;
}

int findratio(std::vector<std::vector<char>> input, int i, int j) {
    std::vector<int> adjs;

    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (!(i+k < 0 || i+k >= input.size() || j+l < 0 || j+l >= input[i].size())) {
                if (isdigit(input[i+k][j+l])) {
                    int num = parsenum(input, i+k, j+l);
                    adjs.push_back(num);
                }

                // skip the rest of the number so it isnt counted twice
                while (isdigit(input[i+k][j+l])) {
                    l++;
                }
            }
        }
    }

    if (adjs.size() == 1) return 0;

    return std::accumulate(adjs.begin(), adjs.end(), 1, std::multiplies<int>());
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<char>> input;
    std::string line;
    int acc = 0;

    while (std::getline(std::cin, line))
    {
        std::vector<char> row(line.begin(), line.end());
        if (row.size() > 0) input.push_back(row);
    }

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '*') {
                acc += findratio(input, i, j);
            }
        }
    }

    std::cout << acc << std::endl;
}