#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

vector<long> parsenums(string str) {
    vector<long> nums;
    stringstream ss(str);
    long num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

int main(int argc, char* argv[])
{
    long acc = 1;

    string line;

    getline(cin, line);
    line.erase(remove_if(line.begin(), line.end(), [](auto x){return isspace(x);}), line.end());
    vector<long> times = parsenums(line.substr(line.find_first_of("0123456789")));
    getline(cin, line);
    line.erase(remove_if(line.begin(), line.end(), [](auto x){return isspace(x);}), line.end());
    vector<long> distances = parsenums(line.substr(line.find_first_of("0123456789")));

    for (int i = 0; i < times.size(); i++) {
        double lower = 0.5 * (times[i] - sqrt(times[i] * times[i] - 4 * distances[i]));
        double upper = 0.5 * (times[i] + sqrt(times[i] * times[i] - 4 * distances[i]));
        acc *= (ceil(upper) -1) - (floor(lower) + 1) + 1;
    }
    cout << acc << endl;
}