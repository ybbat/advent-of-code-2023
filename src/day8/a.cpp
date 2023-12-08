#include <map>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    std::map<std::string, std::pair<std::string, std::string>> graph;

    std::string line;
    getline(std::cin, line);
    auto directions = line;
    getline(std::cin, line);

    while (getline(std::cin, line)) {
        auto parent = line.substr(0, 3);
        auto left = line.substr(7, 3);
        auto right = line.substr(12, 3);

        graph[parent] = std::make_pair(left, right);
    }

    int steps = 0;

    std::string current = "AAA";
    std::string target = "ZZZ";
    while (current != target) {
        for (int i = 0; i < directions.size(); i++) {
            auto direction = directions[i];
            auto next = graph[current];
            if (direction == 'L') {
                current = next.first;
            } else {
                current = next.second;
            }

            steps++;
        }
    }

    std::cout << steps << std::endl;
}