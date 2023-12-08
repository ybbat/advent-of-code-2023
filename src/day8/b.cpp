#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

typedef std::unordered_map<std::string, std::pair<std::string, std::string>> GraphType;

std::vector<std::string> findStarts(GraphType graph)
{
    std::vector<std::string> starts;
    for (auto node : graph) {
        auto key = node.first;
        if (key.back() == 'A') {
            starts.push_back(node.first);
        }
    }
    return starts;
}

int main(int argc, char* argv[])
{
    GraphType graph;

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

    std::vector<std::string> currents = findStarts(graph);
    std::vector<int> steps;

    for (auto& current : currents) {
        int s = 0;
        while (current.back() != 'Z') {
            for (auto direction: directions) {
                auto next = graph[current];
                if (direction == 'L') {
                    current = next.first;
                } else {
                    current = next.second;
                }

                s++;
            }
        }
        steps.push_back(s);
    }

    long acc = 1;
    for (auto step : steps) {
        acc = std::lcm(acc, step);
    }
    std::cout << acc << std::endl;
}