#include <iostream>

int main(int argc, char* argv[])
{
    std::string input;
    int acc = 0;
    while (std::cin >> input) {
        int first = 100;
        int last = 100;
        for (int i = 0; i < input.size(); i++) {
            if (first == 100 && isdigit(input[i])) first = input[i] - '0';
            if (last == 100 && isdigit(input[input.size()-1-i])) last = input[input.size()-1-i] - '0';

            if (first != 100 && last != 100) break;
        }
        acc += 10*first + last;
    }
    std::cout << acc << std::endl;
}