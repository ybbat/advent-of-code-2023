#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
    std::string line;
    int acc = 0;

    int game = 1;
    while (std::getline(std::cin, line))
    {
        int maxr = 0, maxg = 0, maxb = 0;

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
                        maxr = std::max(maxr, num);
                        break;
                    case 'g':
                        maxg = std::max(maxg, num);
                        break;
                    case 'b':
                        maxb = std::max(maxb, num);
                        break;
                }
            }
        }

        acc += maxr * maxg * maxb;

        game++;
    }

    std::cout << acc << std::endl;
}