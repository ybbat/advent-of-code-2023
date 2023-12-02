#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
    std::string line;
    int acc = 0;

    int game = 1;
    while (std::getline(std::cin, line))
    {
        bool valid = true;
        int i = 0;
        while (line[i] != ':') i++; // skip until real data

        for (; i < line.size(); i++)
        {
            int j = 0;
            while (isdigit(line[i+j])) j++;

            int num = 0;
            for (int k = 0; j-k > 0; k++) {
                num += (line[i+j-k-1] - '0') * pow(10, k);
            }

            if (num != 0) {
                switch (line[i+j+1]) {
                    case 'r':
                        if (num > 12) valid = false;
                        break;
                    case 'g':
                        if (num > 13) valid = false;
                        break;
                    case 'b':
                        if (num > 14) valid = false;
                        break;
                }
            }

            if (valid == false) {
                break;
            }
        }

        if (valid) acc += game;
        game++;
    }

    std::cout << acc << std::endl;
}