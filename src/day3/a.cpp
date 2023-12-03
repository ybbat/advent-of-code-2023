#include <iostream>
#include <cmath>
#include <vector>

bool isadj(std::vector<std::vector<char>> input, int i, int j) {
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (!(i+k < 0 || i+k >= input.size() || j+l < 0 || j+l >= input[i].size())) {
                if (ispunct(input[i+k][j+l]) && input[i+k][j+l] != '.') return true;
            }
        }
    }
    return false;
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
            bool adj = false;
            int k = 0;
            while (isdigit(input[i][j+k])) {
                if (isadj(input, i, j+k)) adj=true;
                k++;
            }

            if (adj) {
                int num = 0;
                for (int l = 0; k-l > 0; l++) {
                    num += (input[i][j+k-l-1] - '0') * pow(10, l);
                }
                acc += num;
            }
            j += k;
        }
    }

    std::cout << acc << std::endl;
}