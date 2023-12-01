#include <iostream>

int spelledout(std::string s, int i)
{
    std::string ss = s.substr(i);
    if (ss.starts_with("one")) return 1;
    if (ss.starts_with("two")) return 2;
    if (ss.starts_with("three")) return 3;
    if (ss.starts_with("four")) return 4;
    if (ss.starts_with("five")) return 5;
    if (ss.starts_with("six")) return 6;
    if (ss.starts_with("seven")) return 7;
    if (ss.starts_with("eight")) return 8;
    if (ss.starts_with("nine")) return 9;
    return -1;
}

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

            int val;
            if (first == 100 && (val = spelledout(input, i)) != -1) first = val;
            if (last == 100 && (val = spelledout(input, input.size()-1-i)) != -1) last = val;

            if (first != 100 && last != 100) break;
        }
        acc += 10*first + last;
    }
    std::cout << acc << std::endl;
}