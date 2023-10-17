#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>

namespace aoc_2022_03 {
static int prio(char p) {
    if(std::isupper(p)) {
        return p - 'A' + 27;
    }    
    return p - 'a' + 1;
}

std::vector<std::pair<std::string, std::string>> clean_input(std::vector<std::string> input_data) {
    std::vector<std::pair<std::string, std::string>> rucksacks;
    for (auto& row: input_data) {
        std::pair<std::string, std::string> packs;
        packs.first = row.substr(0, row.length() / 2);
        packs.second = row.substr(row.length() / 2, row.length() / 2);
        rucksacks.push_back(packs);
    }
    return rucksacks;
}

std::vector<std::string> parse(std::string path) {
    std::vector<std::string> data;
    std::fstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
    }
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    return data;
}

int solve_part_1(std::vector<std::pair<std::string, std::string>> data) {
    std::int32_t prio_sum = 0;

    for (auto& pack: data) {
        std::set<char> first(pack.first.begin(), pack.first.end());
        std::set<char> second(pack.second.begin(), pack.second.end());

        std::vector<char> common;
        std::ranges::set_intersection(first, second, std::back_inserter(common));
        prio_sum += prio(common[0]);
    }

    return prio_sum;
}
}

int main(void) {

    std::vector<std::string> data;
    data = aoc_2022_03::parse("c:/home/yy11510/projects/adventofcode/data/2022/03/input.txt");
    auto parsed_data = aoc_2022_03::clean_input(data);

    std::cout << "Part 1 Answer: " << aoc_2022_03::solve_part_1(parsed_data) << std::endl;
    
    return 0;
}
