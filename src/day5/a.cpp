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

bool operator==(const Range& lhs, const Range& rhs) {
    return lhs.first == rhs.first && lhs.last == rhs.last;
}

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
    std::vector<Range> seeds = parseRanges(line.substr(line.find(":") + 1));

    std::vector<Range> before = seeds;
    std::vector<Range> after = seeds;

    std::vector<Range> goingtoadd;

    std::getline(std::cin, line); // skip next line

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            before = after;
            after.clear();
        } else if (isdigit(line[0])) {
            std::vector map = parsenums(line);
            Map m = {map[0], map[1], map[2]};
            Range src_range = {m.source, m.source + m.amount - 1};
            long change = m.dest - m.source;

            std::cout << after.size() << " -> ";

            for (auto r : before) {

                if (r.first >= src_range.first && r.last <= src_range.last) { // CASE 1: r is completely within src_range
                    // std::cout << "CASE 1" << std::endl;
                    after.push_back({r.first + change, r.last + change});
                    std::erase_if(goingtoadd, [r](Range& x) { return x == r; });
                } else if (r.first >= src_range.first && r.first <= src_range.last) { // CASE 2: only r.first is within src_range
                    // std::cout << "CASE 2" << std::endl;
                    after.push_back({r.first + change, src_range.last + change});
                    after.push_back({src_range.last + 1, r.last});
                    std::erase_if(goingtoadd, [r](Range& x) { return x == r; });
                } else if (r.last >= src_range.first && r.last <= src_range.last) { // CASE 3: only r.last is within src_range
                    // std::cout << "CASE 3" << std::endl;
                    after.push_back({r.first, src_range.first - 1});
                    after.push_back({src_range.first + change, r.last + change});
                    std::erase_if(goingtoadd, [r](Range& x) { return x == r; });
                } else if (src_range.first >= r.first && src_range.last <= r.last) { // CASE 4: src_range is commpletely within r
                    // std::cout << "CASE 4" << std::endl;
                    after.push_back({r.first, src_range.first - 1});
                    after.push_back({src_range.first + change, src_range.last + change});
                    after.push_back({src_range.last + 1, r.last});
                    std::erase_if(goingtoadd, [r](Range& x) { return x == r; });
                } else { // CASE 5: no intersection
                    // std::cout << "CASE 5" << std::endl;
                    goingtoadd.push_back(r);
                }
            }
            after.insert(after.end(), goingtoadd.begin(), goingtoadd.end());
            goingtoadd.clear();
            std::cout << after.size() << std::endl;
        }
    }

    // for (aut& r : after) {
    //     std::cout << r.first << " " << r.last << std::endl;
    // }

    long smallest = LONG_MAX;
    for (auto r : after) {
        if (r.first < smallest) {
            smallest = r.first;
        }
    }
    std::cout << smallest << std::endl;
}