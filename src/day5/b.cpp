#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Map {
    long dest;
    long source;
    long amount;
};

struct Range {
    long first;
    long last;
};

std::vector<long> parsenums(std::string str) {
    std::vector<long> nums;
    std::stringstream ss(str);
    long num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

std::vector<Range> parseRanges(std::string str) {
    std::vector<Range> ranges;
    std::stringstream ss(str);

    long start, length;
    while (ss >> start >> length) {
        ranges.push_back({start, start + length - 1});
    }
    return ranges;
}

int main(int argc, char* argv[])
{
    std::string line;

    std::getline(std::cin, line);

    std::vector<Range> before = parseRanges(line.substr(line.find(":") + 1));
    std::vector<Range> after;

    std::vector<Range> unused;

    std::getline(std::cin, line); // skip next line

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            if (!before.empty()) {
                before.insert(before.end(), after.begin(), after.end());
            } else {
                before = after;
            }
            after.clear();
        } else if (isdigit(line[0])) {
            std::vector map = parsenums(line);
            Map m = {map[0], map[1], map[2]};
            Range src_range = {m.source, m.source + m.amount - 1};
            long change = m.dest - m.source;

            while (!before.empty()) {
                Range r = before.back();
                before.pop_back();

                if (r.first >= src_range.first && r.last <= src_range.last) { // CASE 1: r is completely within src_range
                    after.push_back({r.first + change, r.last + change});
                } else if (r.first >= src_range.first && r.first <= src_range.last) { // CASE 2: only r.first is within src_range
                    after.push_back({r.first + change, src_range.last + change});
                    unused.push_back({src_range.last + 1, r.last});
                } else if (r.last >= src_range.first && r.last <= src_range.last) { // CASE 3: only r.last is within src_range
                    unused.push_back({r.first, src_range.first - 1});
                    after.push_back({src_range.first + change, r.last + change});
                } else if (src_range.first >= r.first && src_range.last <= r.last) { // CASE 4: src_range is commpletely within r
                    unused.push_back({r.first, src_range.first - 1});
                    after.push_back({src_range.first + change, src_range.last + change});
                    unused.push_back({src_range.last + 1, r.last});
                } else { // CASE 5: no intersection
                    unused.push_back(r);
                }
            }
            before = unused;
            unused.clear();
        }
    }

    long smallest = LONG_MAX;
    for (auto r : after) {
        if (r.first < smallest) {
            smallest = r.first;
        }
    }
    std::cout << smallest << std::endl;
}